/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:06 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/19 17:42:06 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	my_close(cmd->prev_nb, cmd->infile, cmd->p_nb[1], cmd->outfile);
	if (cmd->next)
		cmd->next->prev_nb = tmp_fd;
	else
		close(cmd->p_nb[0]);
}

void	do_cmd(t_cmd *cmd, t_globale *data)
{
	char	*path;

	path = NULL;
	if (is_builtin(cmd->command[0]))
		do_builtin(data, cmd);
	else if (exist(cmd->command[0], &path, data))
		execve(path, cmd->command, data->env);
	free_exit(data, NULL, data->exit_code);
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

void	wait_all(t_globale *data)
{
	int		signal;
	int		status;
	t_cmd	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		signal = waitpid(0, &status, 0);
		if (signal == data->signal)
		{
			if (WIFEXITED(status))
				data->exit_code = WEXITSTATUS(status);
		}
		tmp = tmp->next;
	}
}

int	exec(t_globale *data)
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
			return (1);
		exec_cmd(cmd, data);
		cmd = cmd->next;
	}
	wait_all(data);
	return (0);
}
