/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:30:35 by romukena          #+#    #+#             */
/*   Updated: 2025/12/10 15:24:56 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	init_var(t_cmd **head_cmd, t_cmd **cur_cmd, t_node **tmp, t_node **head)
{
	*head_cmd = NULL;
	*cur_cmd = NULL;
	*tmp = *head;
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

void	mini_null(t_cmd **cmd, t_node **node)
{
	*cmd = NULL;
	*node = NULL;
}

int	process_command(char *line, t_node **node, char ***env, int prv)
{
	t_cmd	*cmd;

	(lexer(line, node, *env), handle_expands(node, *env, prv));
	cmd = parser(node, &prv);
	(add_history(line), free(line));
	if (cmd)
		prv = exec(cmd, env, *node, prv);
	(clear_nodes(node), free_cmd_list_no_files(cmd));
	return (prv);
}
