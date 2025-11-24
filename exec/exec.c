/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:06 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/24 17:38:55 by ydembele         ###   ########.fr       */
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
	else if (cmd->argv && !cmd->argv[0])
		exec->exit_code = 126;
	else if (exist(&path, cmd, data, exec))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->argv, data->env);
		perror("execve");
		exec->exit_code = 127;
		free(path);
	}
	free_exit(data, NULL, exec->exit_code);
}

void	exec_cmd(t_exec *exec, t_globale *data)
{
	t_redir	*list;

	(void)list;
	if (exec->skip_cmd || (!exec->cmd->argv))
	{
		next(exec);
		exec->exit_code = 1;
		if (!exec->cmd->argv)
			exec->exit_code = 0;
	}
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
	if (exec->skip_cmd == false)
		do_builtin(data, exec);
	else
		exec->exit_code = 1;
	*env = data->env;
	exit_code = exec->exit_code;
	return (free_exec(data), exit_code);
}

int	exec_line(t_globale *data)
{
	t_exec	*exec;
	int		ex_code;

	ex_code = 0;
	exec = data->exec;
	open_file(exec);
	while (exec)
	{
		ex_code = 0;
		if (pipe(exec->p_nb) == -1)
		{
			perror("pipe");
			exec->exit_code = 1;
			return (1);
		}
		exec_cmd(exec, data);
		ex_code = exec->exit_code;
		exec = exec->next;
	}
	return (ex_code);
}

int	exec(t_cmd *command, char ***env, t_node *node, int prv_code)
{
	t_globale	*data;
	int			exit_code;
	int			err;

	err = 0;
	data = malloc(sizeof(t_globale));
	data->env = *env;
	data->exec = init_exec(command);
	init_data(data, node, prv_code);
	exit_code = 0;
	if ((data->exec && data->exec->next == NULL)
		&& data->exec->cmd->argv && data->exec->cmd->argv[0]
		&& is_builtin(data->exec->cmd->argv[0]))
		return (exec_builtin(data, env));
	err = exec_line(data);
	wait_all(&exit_code);
	*env = data->env;
	free_exec(data);
	if (err)
		return (err);
	return (exit_code);
}
