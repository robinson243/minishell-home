#include "../minishell.h"

// int	wait_doc(int p[2], pid_t pid)
// {
// 	close(p[1]);
// 	close(p[0]);
// 	x->prev_nb[0] = x->fd[0];
// 	waitpid(pid, NULL, 0);
// }

int	here_doc(t_list *file)
{
	pid_t	pid;
	int		p[2];
	char	*line;

	line = NULL;
	if (pipe(p) == -1)
		exit(1);
	pid = fork();
	if (pid == 0)
	{
		close(p[0]);
		while (1)
		{
			free(line);
			line = readline("> ");
			if (!line)
				break ;
			if (ft_strncmp(line, file->path, ft_strlen(file->path)) == 0
				&& line[ft_strlen(line)] == '\n')
			{
				free(line);
				exit(0);
			}
			write(p[1], line, ft_strlen(line));
		}
		close(p[1]);
		exit(0);
	}
	else
		wait_doc(pid);
}

void	next(t_cmd *cmd)
{
	int	tmp_fd;

	tmp_fd = cmd->p_nb[0];
	my_close(cmd->prev_nb, -1, cmd->p_nb[1], -1);
	if (cmd->next)
		cmd->next->prev_nb = tmp_fd;
	//	x->n_pid++; // compteur de fork
}

char	*get_path(char **env, char *cmd)
{
	int		i;
	char	**local;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			local = ft_split(env[i] + 5, ':');
			if (!local)
				return (0);
		}
		i++;
	}
	i = 0;
	if (!local)
		return (0);
	while (local[i])
	{
		path = ft_strslashjoin(local[i++], cmd);
		if (!path)
			return (free_all(local), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free_all(local), path);
		free(path);
	}
	return (free_all(local), NULL);
}

void	do_cmd(t_cmd *cmd, t_globale *data)
{
	// if (is_builtin(cmd->command[0]))
	// 	return (do_builtin(cmd));
	char	*path;

	path = NULL;
	if (access(cmd->command[0], F_OK | X_OK) == 0)
		path = ft_strdup(cmd->command[0]);
	else
		path = get_path(data->env, cmd->command[0]);
	if (!path)
		exit(1);
	execve(path, cmd->command, data->env);
	exit(127);
}

void	exec_cmd(t_cmd *cmd, t_globale *data)
{
	int		signal;
	t_list	*list;

	list = cmd->list;
	cmd->infile = -1;
	cmd->outfile = -1;
	if (cmd->list)
	{
		while (cmd->list)
		{
			if (cmd->list->type == INFILE || cmd->list->type == HEREDOC)
				my_close(cmd->infile, -1, -1, -1);
			else
				my_close(cmd->outfile, -1, -1, -1);
			if (!my_open(cmd->list, cmd))
				return (0);
			cmd->list = cmd->list->next;
		}
	}
	signal = fork();
	if (signal == -1)
		exit(1);
	if (signal == 0)
	{
		redir_in_out(cmd);
		do_cmd(cmd, data);
	}
	else
		next(cmd);
}

void	exec(t_globale *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (pipe(cmd->p_nb) == -1)
			exit(1);
		exec_cmd(cmd, data);
		cmd = cmd->next;
	}
}
