/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:41:37 by romukena          #+#    #+#             */
/*   Updated: 2025/11/01 16:35:15 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	numb_of_commands(t_node **head)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = *head;
	if (!head || !(*head))
		return (i) ;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (i);
}

t_cmd *new_cmd(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	return (node);
}

t_redir *new_redir(int type, char *file)
{
	t_redir *node;
	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->file = file;
	node->type = type;
	return (node);
}

void add_redir(t_cmd *cmd, t_redir *new)
{
	if (!cmd->redir)
	{
		cmd->redir = new;
		return ;
	}
	while (cmd->redir->next)
		cmd->redir = cmd->redir->next;
	cmd->redir = new;
}

void add_arg(t_cmd *cmd, char *arg)
{
	
}