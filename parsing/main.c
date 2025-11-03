/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/11/03 15:49:20 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_cmd	*cmd;
	t_node	*node;

	node = NULL;
	cmd = NULL;
	using_history();
	(void)ac;
	(void)av;
	while ((line = readline("minishell > ")))
	{
		lexer(line, &node);
		handle_expands(&node);
		cmd = parser(&node);
		print_cmd_list(cmd);
		free_cmd_list_no_files(cmd);
		clear_nodes(&node);
		add_history(line);
		free(line);
	}
	clear_history();
}
