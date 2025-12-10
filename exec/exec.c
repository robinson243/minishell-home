/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:06 by ydembele          #+#    #+#             */
/*   Updated: 2025/12/10 11:55:44 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	do_cmd(t_exec *exec, t_globale *data)
{
	char	*path;
	char	**argv;

	path = NULL;
	redir_in_out(exec);
	if (exec->skip_cmd)
		free_exit(data, NULL, 1);
	if (is_builtin(exec->cmd->argv[0]))
		do_builtin(data, exec);
	else if (!exec->cmd->argv || !exec->cmd->argv[0])
		exec->exit_code = 126;
	else if (exist(&path, exec->cmd, data, exec))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		argv = expand_star_argv(exec->cmd->argv);
		execve(path, argv, data->env);
		perror("execve");
		exec->exit_code = 127;
		free(path);
		free_all(argv);
	}
	free_exit(data, NULL, exec->exit_code);
}

int	exec_cmd(t_exec *exec, t_globale *data)
{
	if (exec->skip_cmd || (!exec->cmd->argv))
	{
		next(exec);
		exec->exit_code = 1;
		if (!exec->cmd->argv && !exec->skip_cmd)
			exec->exit_code = 0;
	}
	else
	{
		data->g_signal = fork();
		if (data->g_signal == -1)
			return (ft_putstr_fd("Fork\n", 2), 0);
		if (data->g_signal == 0)
			do_cmd(exec, data);
		else
		{
			signal(SIGINT, handle_sigint_child);
			signal(SIGQUIT, SIG_IGN);
			next(exec);
		}
	}
	return (1);
}

int	exec_builtin(t_globale *data, char ***env)
{
	t_exec	*exec;
	int		exit_code;

	exec = data->exec;
	open_file(exec, data->env);
	if (exec->skip_cmd == false)
		do_builtin(data, exec);
	else
		exec->exit_code = 1;
	exit_code = exec->exit_code;
	*env = data->env;
	free_exec(data);
	return (exit_code);
}

int	exec_line(t_globale *data, int *i)
{
	t_exec	*exec;
	int		ex_code;

	ex_code = 0;
	exec = data->exec;
	open_file(exec, data->env);
	while (exec)
	{
		i++;
		ex_code = 0;
		if (pipe(exec->p_nb) == -1)
		{
			perror("pipe");
			exec->exit_code = 1;
			return (1);
		}
		if (!exec_cmd(exec, data))
			return (ft_putstr_fd("Fork error\n", 2), 1);
		ex_code = exec->exit_code;
		exec = exec->next;
	}
	return (ex_code);
}

int	exec(t_cmd *command, char ***env, t_node *node, int prv_code)
{
	t_globale	*data;
	int			err;
	int			i;

	i = 0;
	err = 0;
	data = malloc(sizeof(t_globale));
	if (!data)
		return (ft_putstr_fd("Error malloc !", 2), 1);
	data->env = *env;
	data->exec = init_exec(command, data);
	if (!data->exec)
		return (1);
	init_data(data, node, prv_code);
	err = 0;
	if ((data->exec && data->exec->next == NULL)
		&& data->exec->cmd->argv && data->exec->cmd->argv[0]
		&& is_builtin(data->exec->cmd->argv[0]))
		return (exec_builtin(data, env));
	err = exec_line(data, &i);
	wait_all(&err, data->g_signal);
	*env = data->env;
	free_exec(data);
	return (err);
}
