/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 16:38:13 by ydembele          #+#    #+#             */
/*   Updated: 2025/12/10 15:25:38 by ydembele         ###   ########.fr       */
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

void	write_line(char *line, char **env, int fd)
{
	int		i;
	int		j;
	char	*word;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			j = 0;
			word = expand_dollar_basic(line, &i, env);
			while (word && word[j])
				write(fd, &word[j++], 1);
			while (line[i] && line[i] != ' ')
				i++;
			free(word);
		}
		else
			write(fd, &line[i++], 1);
	}
	write(fd, "\n", 1);
	free(line);
}

void	heredoc_loop(char *limiter, char **env, t_globale *data)
{
	int		fd;
	char	*line;

	(void)data;
	// free_exit(data, NULL, -1);
	fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write_line(line, env, fd);
	}
	close(fd);
}

int	my_here_doc(char *limiter, char **env, t_globale *data)
{
	pid_t	pid;
	int		status;
	int		fd;

	status = 0;
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		signal(SIGINT, sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
		heredoc_loop(limiter, env, data);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sigint);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (-1);
	fd = open(".tmp", O_RDONLY);
	unlink(".tmp");
	if (fd == -1)
		return (-1);
	return (fd);
}
