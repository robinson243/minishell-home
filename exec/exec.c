/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:06 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/15 17:38:04 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	next(t_exec *exec)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (exec->next)
		tmp_fd = exec->p_nb[0];
	my_close(exec->prev_nb, exec->infile, exec->p_nb[1], exec->outfile);
	if (exec->next)
		exec->next->prev_nb = tmp_fd;
	else if (exec->p_nb[0] >= 0)
		close(exec->p_nb[0]);
}

void	do_cmd(t_exec *exec, t_globale *data)
{
	char	*path;
	t_cmd	*cmd;

	cmd = exec->cmd;
	path = NULL;
	redir_in_out(exec);
	if (exec->skip_cmd)
		free_exit(data, NULL, 1);
	if (is_builtin(cmd->argv[0]))
		do_builtin(data, exec);
	else if (exist(&path, cmd, data, exec))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->argv, data->env);
		free(path);
	}
	free_exit(data, NULL, exec->exit_code);
}

void	exec_cmd(t_exec *exec, t_globale *data)
{
	t_redir	*list;
	t_cmd	*cmd;

	cmd = exec->cmd;
	(void)list;
	if (exec->skip_cmd)
	{
		next(exec);
		exec->exit_code = 1;
	}
	else if (!cmd->argv || !cmd->argv[0])
		exec->exit_code = 0;
	else
	{
		g_signal = fork();
		if (g_signal == -1)
			free_exit(data, "Fork", 1);
		if (g_signal == 0)
			do_cmd(exec, data);
		else
		{
			signal(SIGINT, handle_sigint_child);
			signal(SIGQUIT, SIG_IGN);
			next(exec);
		}
	}
}

void	wait_all(int *exit_code)
{
	pid_t	pid;
	int		status;
	int		sig;

	while ((pid = waitpid(-1, &status, 0)) > 0)
	{
		if (pid == g_signal)
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
	setup_signals_parent();
}

int	exec(t_cmd *command, char **env, t_node *node, int prv_code)
{
	t_exec		*exec;
	int			exit_code;
	t_globale	*data;

	data = malloc(sizeof(t_globale));
	data->env = env;
	data->exec = init_exec(command);
	init_data(data, node, prv_code);
	exit_code = 0;
	exec = data->exec;
	if ((exec && exec->next == NULL) && exec->cmd->argv && exec->cmd->argv[0]
		&& is_builtin(exec->cmd->argv[0]))
	{
		open_file(exec);
		if (!exec->skip_cmd)
			do_builtin(data, exec);
		return (exec->exit_code);
	}
	open_file(exec);
	while (exec)
	{
		if (pipe(exec->p_nb) == -1)
			return (1);
		exec_cmd(exec, data);
		exec = exec->next;
	}
	wait_all(&exit_code);
	free_exec(data);
	return (exit_code);
}
