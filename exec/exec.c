#include "../minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	my_open(t_file *list)
{
	if (!list || !list->path)
		return (-1);
	if (list->way_open == INFILE)
		list->fd = open(list->path, O_RDONLY);
	else if (list->way_open == OUTFILE)
		list->fd = open(list->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (list->way_open == OUT_APPEND)
		list->fd = open(list->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (list->way_open == HEREDOC)
		list->fd = heredoc();
	else
		list->fd = -1;
	if (list->fd == -1)
	{
		perror(list->path);
		return (-1);
	}
	return (list->fd);
}

// void	skip_file(t_globale *data, t_cmd *cmd)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	while (cmd->skipfile[i])
// 	{
// 		fd = my_open(cmd->skipfile[i]); // MY_OPEN
// 		if (fd == -1)
// 		{
// 			perror(cmd->skipfile[i]->path);
// 			cmd->skip_cmd = true;
// 			return ;
// 		}
// 		close(cmd->skipfile[i]->path);
// 	}
// }

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
	char	*path;

	path = NULL;
	if (access(cmd->command[0], F_OK | X_OK) == 0)
	{
		path = ft_strdup(cmd->command[0]);
		if (!path)
			exit(1);
	}
	else
		path = get_path(data->env, cmd->command[0]);
	if (!path)
		exit(1);
	execve(path, cmd->command, data->env);
}

void	redir_in(t_cmd *cmd)
{
	int	infile;

	infile = -1;
	if (cmd->first == 0 && !cmd->inf)
	{
		if (dup2(cmd->prev_nb, 0) == -1)
			cmd->skip_cmd = true;
	}
	else if (cmd->inf)
	{
		infile = my_open(cmd->inf);
		if (infile == -1)
			cmd->skip_cmd = true;
		else if (dup2(infile, 0) == -1)
			cmd->skip_cmd = true;
	}
	if (infile != -1)
		close(infile);
}

void	redir_out(t_cmd *cmd)
{
	int	outfile;

	outfile = -1;
	if (cmd->next != NULL && !cmd->out)
	{
		if (dup2(cmd->p_nb[1], 1) == -1)
			cmd->skip_cmd = true;
	}
	else if (cmd->out)
	{
		outfile = my_open(cmd->out);
		if (outfile == -1)
			cmd->skip_cmd = true;
		else if (dup2(outfile, 1) == -1)
			cmd->skip_cmd = true;
	}
	if (outfile != -1)
		close(outfile);
}

void	redir_in_out(t_cmd *cmd)
{
	if (cmd->inf)
}

void	exec_cmd(t_cmd *cmd, t_globale *data)
{
	int	signal;

	signal = fork();
	if (signal == -1)
		exit(1);
	if (cmd->list)
	{
		while (cmd->list)
		{
		my_open()
			// if (cmd->list->type == REDIR_OUT)
			// {
			// 	fd = open(cmd->list->path, O_RDONLY | O_CREAT);
			// 	dup2(fd, 1);
			// 	close(fd);
			// }
			// if (cmd->list->type == REDIR_IN)
			// {
			// 	fd = open(cmd->list->path, O_RDONLY | O_CREAT);
			// 	if (/* fd < 0 */)

			// 	dup2(fd, 1);
			// 	close(fd);
			// }
			// if (cmd->list->type == REDIR_APPEND)
			// {
			// 	fd = open(cmd->list->path, O_RDONLY | O_CREAT);
			// 	dup2(fd, 1);
			// 	close(fd);
			// }
			// // gere heredoc ici 
		}
	}
	if (signal)
	{
		skip_file(data, cmd);
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
	int		p[2];
	pid_t pid1;
	pid_t pid2;

	cmd = data->cmd;
	while (cmd)
	{
		if (pipe(p) == -1)
			exit(1);
		
		exec_cmd(cmd, data);
	}
}
