/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/11/03 12:10:52 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// int	main(void)
// {
// 	t_node	*head;
// 	// t_cmd	*final_head;
// 	int		i;

// 	// char *str = "cat /etc/passwd | grep \"/bin/bash\" | cut -d: -f1 | sort | uniq | tr 'a-z' 'A-Z'";
// 	// lexer(str, &head);
// 	// handle_expands(&head);
// 	// print_list(&head);
// 	// int val = numb_of_commands(&head);
// 	// printf("\nnumber is %d\n", val);
// 	vivi();
// 	return (0);
// }

int main(void)
{
	t_cmd *cmd = new_cmd();

	add_arg(cmd, "ls");
	add_arg(cmd, "-l");
	add_arg(cmd, "/home");

	printf("Arguments ajoutés :\n");
	for (int i = 0; cmd->argv && cmd->argv[i]; i++)
		printf("[%s]\n", cmd->argv[i]);

	// libération simple
	for (int i = 0; cmd->argv && cmd->argv[i]; i++)
		free(cmd->argv[i]);
	free(cmd->argv);
	free(cmd);
	return (0);
}
