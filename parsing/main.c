/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dems <dems@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/11/06 15:04:34 by dems             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reldnah <reldnah@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:43:55 by reldnah           #+#    #+#             */
/*   Updated: 2023/05/12 11:31:50 by reldnah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	clear_rl_line(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
}

static void	handle_sigint(int code)
{
	(void)code;
	printf("\n");
	clear_rl_line();
	if (g_signal == 0)
		rl_redisplay();
}

static void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 19);
	exit(11);
}

static void	handle_sigabrt(int code)
{
	(void)code;
	write(1, "abort\n", 6);
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_node	*node;
	char	**env;

	env = ft_strdupdup(envp);
	node = NULL;
	cmd = NULL;
	using_history();
	(void)ac;
	(void)av;
	signals();
	while ((line = readline("minishell > ")))
	{
		lexer(line, &node);
		handle_expands(&node);
		cmd = parser(&node);
		//print_cmd_list(cmd);
		clear_nodes(&node);
		exec(cmd, env);
		free_cmd_list_no_files(cmd);
		add_history(line);
		free(line);
	}
	clear_history();
}
