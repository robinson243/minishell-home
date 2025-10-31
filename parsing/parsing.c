/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:41:37 by romukena          #+#    #+#             */
/*   Updated: 2025/10/30 23:36:35 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

/* char **gives_cmd(t_node **head)
{
	t_node *tmp;
	char **cmd;
	int	i;
	
	i = 0;
	cmd = malloc(sizeof(char *)* 200);
	tmp = *head;
	if (*head || !head)
		return (NULL);
	cmd[i] = tmp->content;
	while (tmp)
	{
		if (tmp->type == WORD && ft_strcmp(tmp->content[0],"-") == 0)
		{
			cmd[i] = tmp->content;
			i++;
		}
		if (tmp->type == PIPE)
			return (cmd);
		tmp->next;
	}
	return (cmd);
} */