#include "../minishell.h"

void	skip_file(t_globale *data, t_cmd *cmd)
{
	int	i;

	i = 1;
}

void	next(t_cmd *cmd)
{
	int	tmp_fd;

	tmp_fd = cmd->p_nb[0];
	my_close(cmd->prev_nb, -1, cmd->p_nb[1], -1);
	cmd->prev_nb = tmp_fd;
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
	if (access(cmd->command[0], F_OK | X_OK) == 0)
	{
		cmd->path = ft_strdup(cmd->command[0]);
		if (!cmd->path)
			exit(1);
	}
	else
		cmd->path = get_path(cmd->env, cmd->command[0]);
	if (!cmd->path)
		exit(1);
	execve(cmd->path, cmd->command, data->env);
}

void	redir_in_out(t_cmd *cmd)
{
	int	infile;
	int	outfile;

	infile = -1;
	outfile = -1;
	if (cmd->first == 0 && !cmd->inf)
		dup2(cmd->prev_nb, 0);
	else if (cmd->inf)
	{
		infile = open(cmd->inf, O_RDONLY);
		if (infile == -1)
			exit(1);
		dup2(infile, 0);
	}
	// else if (cmd->here_doc)	// A FAIRE
	// 	;
	if (cmd->next != NULL && !cmd->out)
	{
		if (dup2(cmd->p_nb[1], 1) == -1)
			exit(1);
	}
	else if (cmd->out)
	{
		outfile = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644); //MY_OPEN
		if (dup2(outfile, 1) == -1)
			exit(1);
	}
	my_close(infile, outfile, cmd->p_nb[1], cmd->prev_nb);
	close(cmd->p_nb[0]);
}

void	exec_cmd(t_cmd *cmd, t_globale *data)
{
	int	signal;

	signal = fork();
	if (signal)
	{
		redir_in_out(cmd);
		do_cmd(cmd, data);
		exit(127);
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
	}
}
