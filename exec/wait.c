/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:35:05 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/17 11:35:47 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	handle_status(int status, int *exit_code)
{
	int	sig;

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

void	wait_all(int *exit_code)
{
	pid_t	pid;
	int		status;

	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
		if (pid == g_signal)
			handle_status(status, exit_code);
	}
	setup_signals_parent();
}
