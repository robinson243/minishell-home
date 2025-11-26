/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/11/26 14:58:07 by romukena         ###   ########.fr       */
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

bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (true);
	}
	return (false);
}

/*int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_node	*node;
	char	**env;
	int		prv_code;

	prv_code = 0;
	env = ft_strdupdup(envp);
	node = NULL;
	cmd = NULL;
	using_history();
	(void)ac;
	(void)av;
	signals();
	g_signal = 0;
	while ((line = readline("minishell > ")))
	{
		if (empty_line(line))
			continue ;
		lexer(line, &node, env);
		handle_expands(&node, env, prv_code);
		cmd = parser(&node, &prv_code);
		// print_cmd_list(cmd);
		// print_list(&node);
		add_history(line);
		free(line);
		if (cmd)
        	prv_code = exec(cmd, &env, node, prv_code);
		clear_nodes(&node);
		free_cmd_list_no_files(cmd);
		g_signal = 0;
	}
	free_all(env);
	clear_history();
	return (prv_code);
}*/


char	*my_gnl_stdin(void)
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
	node = NULL;
	cmd = NULL;
	using_history();
	(void)ac;
	(void)av;
	signals();
	g_signal = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("minishell > ");
		else
			line = my_gnl_stdin();
		if (!line)
			break ;
		if (empty_line(line))
		{
			free(line);
			continue ;
		}
		lexer(line, &node, env);
		handle_expands(&node, env, prv_code);
		cmd = parser(&node, &prv_code);
		add_history(line);
		free(line);
		prv_code = exec(cmd, &env, node, prv_code);
		clear_nodes(&node);
		free_cmd_list_no_files(cmd);
		g_signal = 0;
	}
	free_all(env);
	clear_history();
	return (prv_code);
}
