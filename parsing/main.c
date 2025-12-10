/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/12/10 11:23:10 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	g_exitcode;

void	handle_sigint(int sig)
{
	(void)sig;
	g_exitcode = 130;
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

	g_exitcode = 0;
	env = ft_strdupdup(envp);
	mini_null(&cmd, &node);
	(using_history(), (void)ac, (void)av, signals());
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break ;
		if (empty_line(line))
			continue ;
		g_exitcode = process_command(line, &node, &env, g_exitcode);
	}
	(free_all(env), clear_history());
	return (g_exitcode);
}
