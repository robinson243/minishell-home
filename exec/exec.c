/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:06 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/17 13:50:43 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

	(void)list;
	if (exec->skip_cmd)
	{
		next(exec);
		exec->exit_code = 1;
	}
	else if (!exec->cmd->argv || !exec->cmd->argv[0])
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

int	exec_builtin(t_globale *data, char ***env)
{
	t_exec	*exec;
	int		exit_code;

	exec = data->exec;
	open_file(exec);
	if (!exec->skip_cmd)
		do_builtin(data, exec);
	*env = data->env;
	exit_code = exec->exit_code;
	return (free_exec(data), exit_code);
}

int	exec_line(t_globale *data)
{
	t_exec	*exec;

	exec = data->exec;
	while (exec)
	{
		open_file(exec);
		if (pipe(exec->p_nb) == -1)
		{
			perror("pipe");
			exec->exit_code = 1;
			return (1);
		}
		exec_cmd(exec, data);
		exec = exec->next;
	}
	return (0);
}

int	exec(t_cmd *command, char ***env, t_node *node, int prv_code)
{
	t_globale	*data;
	int			exit_code;
	int			err_pipe;

	err_pipe = 0;
	data = malloc(sizeof(t_globale));
	data->env = *env;
	data->exec = init_exec(command);
	init_data(data, node, prv_code);
	exit_code = 0;
	if ((data->exec && data->exec->next == NULL)
		&& data->exec->cmd->argv && data->exec->cmd->argv[0]
		&& is_builtin(data->exec->cmd->argv[0]))
		return (exec_builtin(data, env));
	err_pipe = exec_line(data);
	wait_all(&exit_code);
	*env = data->env;
	free_exec(data);
	if (err_pipe)
		return (1);
	return (exit_code);
}
