/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/12/03 16:25:33 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

pid_t		g_signal;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_node	*node;
	char	**env;
	int		prv_code;

	prv_code = 0;
	env = ft_strdupdup(envp);
	mini_null(&cmd, &node);
	(using_history(), (void)ac, (void)av, signals());
	g_signal = 0;
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break ;
		if (empty_line(line))
			continue ;
		prv_code = process_command(line, &node, &env, prv_code);
	}
	(free_all(env), clear_history());
	return (prv_code);
}

/*char	*my_gnl_stdin(void)
{
	char	buffer[4096];
	char	*line;
	size_t	len;

	if (!fgets(buffer, sizeof(buffer), stdin))
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	line = malloc(len + 2);
	if (!line)
		return (NULL);
	for (size_t i = 0; i < len; i++)
		line[i] = buffer[i];
	if (buffer[len] == '\n')
	{
		line[len] = '\n';
		len++;
	}
	line[len] = '\0';
	return (line);
}*/
