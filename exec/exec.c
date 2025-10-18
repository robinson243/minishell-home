#include "../minishell.h"

// int	wait_doc(int p[2], pid_t pid)
// {
// 	close(p[1]);
// 	close(p[0]);
// 	x->prev_nb[0] = x->fd[0];
// 	waitpid(pid, NULL, 0);
// }

int	here_doc(t_file *file)
{
	char	*line;
	int		infile;

	infile = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		return (-1);
	line = NULL;
	while (1)
	{
		free(line);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, file->path, INT_MAX) == 0)
		{
			free(line);
			break ;
		}
		write(infile, line, ft_strlen(line));
	}
	close(infile);
	infile = open(".tmp", O_RDONLY);
	if (infile != -1)
		unlink(".tmp");
	return (infile);
}

void	next(t_cmd *cmd)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (cmd->next)
		tmp_fd = cmd->p_nb[0];
	my_close(cmd->prev_nb, -1, cmd->p_nb[1], -1);
	if (cmd->next)
		cmd->next->prev_nb = tmp_fd;
	else
		close(cmd->p_nb[0]);
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
	char	*path;

	if (is_builtin(cmd->command[0]))
	{
		do_builtin(data, cmd);
		return ;
	}
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

int	open_file(t_cmd *cmd)
{
	t_file	*tmp;
	t_cmd	*command;

	command = cmd;
	while (command)
	{
		tmp = command->list;
		command->infile = -1;
		command->outfile = -1;
		if (!command->list)
		{
			command = command->next;
			continue ;
		}
		while (tmp)
		{
			if (tmp->type == INFILE || tmp->type == HEREDOC)
				my_close(command->infile, -1, -1, -1);
			else
				my_close(command->outfile, -1, -1, -1);
			if (!my_open(tmp, command))
			{
				command->skip_cmd = true;
				break ;
			}
			tmp = tmp->next;
		}
		command = command->next;
	}
	return (0);
}

void	exec_cmd(t_cmd *cmd, t_globale *data)
{
	t_file	*list;

	if (cmd->skip_cmd)
	{
		next(cmd);
		cmd->exit_code = 1;
		return ;
	}
	data->signal = fork();
	if (data->signal == -1)
		exit(1);
	if (data->signal == 0)
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
	if ((cmd && cmd->next == NULL) && is_builtin(cmd->command[0]))
	{
		if (cmd->list)
			open_file(cmd);
		do_builtin(data, cmd);
	}
	open_file(cmd);
	while (cmd)
	{
		if (cmd->next && pipe(cmd->p_nb) == -1)
			exit(1);
		exec_cmd(cmd, data);
		cmd = cmd->next;
	}
}
