/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:13 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/03 17:18:02 by ydembele         ###   ########.fr       */
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


int	my_here_doc(t_redir *file, t_cmd *cmd)
{
	pid_t	pid;
	int		fd;
	int		status;


	pid = fork();
	if (pid == 0)
	{
		fd = here_doc(file);
		if (fd == -1)
			exit(1);
		exit(0);
	}
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
	{
		cmd->skip_cmd = true;
		unlink(".tmp");
		return (0);
	}
	fd = open(".tmp", O_RDONLY);
	unlink(".tmp");
	if (fd != -1)
		cmd->skip_cmd = true;
	return (fd);
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
		if (ft_strncmp(line, file->file, INT_MAX) == 0)
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
