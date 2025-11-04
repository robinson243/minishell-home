/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 18:45:06 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/04 15:07:48 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

pid_t	g_signal;

void	sigint_main(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


t_exec	*init_data(t_cmd *cmd)
{
	t_exec		*head;
	t_exec		*curr;
	t_exec		*new;
	t_cmd		*tmp;

	head = NULL;
	curr = NULL;
	tmp = cmd;
	while (tmp)
	{
		new = malloc(sizeof(t_exec));
		new->cmd = tmp;
		new->skip_cmd = false;
		new->exit_code = 0;
		new->first = (tmp == cmd);
		new->prev_nb = -1;
		new->infile = -1;
		new->outfile = -1;
		new->p_nb[0] = -1;
		new->p_nb[1] = -1;
		new->next = NULL;
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		tmp = tmp->next;
	}
	return (head);
}

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
	if (exec->skip_cmd)
		free_exit(data, NULL, 1);
	if (is_builtin(cmd->argv[0]))
		do_builtin(data, exec);
	else if (exist(&path, cmd, data, exec))
	{
		execve(path, cmd->argv, data->env);
		free(path);
	}
	free_exit(data, NULL, exec->exit_code);
}

void	exec_cmd(t_exec *exec, t_globale *data)
{
	t_redir	*list;
	t_cmd	*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	cmd = exec->cmd;
	if (exec->skip_cmd)
	{
		next(exec);
		exec->exit_code = 1;
		return ;
	}
	g_signal = fork();
	if (g_signal == -1)
		free_exit(data, "Fork", 1);
	if (g_signal == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		redir_in_out(exec);
		do_cmd(exec, data);
	}
	else
		next(exec);
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
			break ;
		}
	}
}

int	exec(t_cmd *command, char **env)
{
	t_exec		*exec;
	int			exit_code;
	t_globale	*data;

	signal(SIGINT, sigint_main);
	signal(SIGQUIT, SIG_IGN);
	data = malloc(sizeof(t_globale));
	data->exec = init_data(command);
	data->env = env;
	exit_code = 0;
	exec = data->exec;
	if ((exec && exec->next == NULL) && is_builtin(exec->cmd->argv[0]))
	{
		open_file(exec);
		if (!exec->skip_cmd)
			do_builtin(data, exec);
		return (0);
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
	return (exit_code);
}
