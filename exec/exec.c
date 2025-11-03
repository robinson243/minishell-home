/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:06 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/03 17:25:38 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

pid_t	g_signal;

void	next(t_cmd *cmd)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (cmd->next)
		tmp_fd = cmd->p_nb[0];
	my_close(cmd->prev_nb, cmd->infile, cmd->p_nb[1], cmd->outfile);
	if (cmd->next)
		cmd->next->prev_nb = tmp_fd;
	else if (cmd->p_nb[0] >= 0)
		close(cmd->p_nb[0]);
}

void	do_cmd(t_cmd *cmd, t_globale *data)
{
	char	*path;

	path = NULL;
	if (cmd->skip_cmd)
		free_exit(data, NULL, 1);
	if (is_builtin(cmd->argv[0]))
		do_builtin(data, cmd);
	else if (exist(cmd->argv[0], &path, cmd, data))
	{
		execve(path, cmd->argv, data->env);
		free(path);
	}
	free_exit(data, NULL, cmd->exit_code);
}

void	exec_cmd(t_cmd *cmd, t_globale *data)
{
	t_redir	*list;

	if (cmd->skip_cmd)
	{
		next(cmd);
		cmd->exit_code = 1;
		return ;
	}
	g_signal = fork();
	if (g_signal == -1)
		free_exit(data, "Fork", 1);
	if (g_signal == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redir_in_out(cmd);
		do_cmd(cmd, data);
	}
	else
		next(cmd);
}

void	wait_all(int *exit_code)
{
	int		signal;
	int		status;
	int		sig;

	while ((signal = waitpid(-1, &status, 0)))
	{
		if (signal == g_signal)
		{
			if (WIFEXITED(status))
				*exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				if (sig == SIGINT)
					*exit_code = 130;
				else if (sig == SIGQUIT)
				{
					write(2, "Quit (core dumped)\n", 19);
					*exit_code = 131;
				}
			}
		}
	}
}

int	exec(t_cmd *command, char **env)
{
	t_cmd		*cmd;
	int			exit_code;
	t_globale	*data;

	data = malloc(sizeof(t_globale));
	data->env = env;
	data->cmd = command;
	exit_code = 1;
	cmd = data->cmd;
	if ((cmd && cmd->next == NULL) && is_builtin(cmd->argv[0]))
	{
		open_file(cmd);
		if (!cmd->skip_cmd)
			do_builtin(data, cmd);
		return (0);
	}
	open_file(cmd);
	while (cmd)
	{
		if (cmd->next && pipe(cmd->p_nb) == -1)
			return (1);
		exec_cmd(cmd, data);
		cmd = cmd->next;
	}
	wait_all(&exit_code);
	return (exit_code);
}
