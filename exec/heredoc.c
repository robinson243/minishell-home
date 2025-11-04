/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:13 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/04 14:57:36 by ydembele         ###   ########.fr       */
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

int	here_doc(t_redir *file)
{
	char	*line;
	int		infile;

	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, SIG_IGN);
	infile = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (strcmp(line, file->file) == 0)
		{
			free(line);
			break ;
		}
		write(infile, line, ft_strlen(line));
		write(infile, "\n", 1);
		free(line);
	}
	close(infile);
	exit(0);
}

int	my_here_doc(t_redir *file, t_cmd *cmd, t_exec *exec)
{
	pid_t	pid;
	int		fd;
	int		status;

	(void)cmd;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		fd = here_doc(file);
		exit(0);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		exec->skip_cmd = true;
		unlink(".tmp");
		return (-1);
	}
	fd = open(".tmp", O_RDONLY);
	unlink(".tmp");
	if (fd == -1)
		return (perror(".tmp"), -1);
	return (fd);
}
