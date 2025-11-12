/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:13 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/11 12:22:44 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	sigint_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	unlink(".tmp");
	exit(130);
}

static void	heredoc_loop(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	exit(0);
}

int	my_here_doc(char *limiter)
{
	pid_t	pid;
	int		status;
	int		fd;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		heredoc_loop(limiter);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	g_signal = 0;
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (-1);
	fd = open(".tmp", O_RDONLY);
	unlink(".tmp");
	if (fd == -1)
		return (-1);
	return (fd);
}
