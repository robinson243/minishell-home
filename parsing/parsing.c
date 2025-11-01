/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:41:37 by romukena          #+#    #+#             */
/*   Updated: 2025/11/01 18:11:02 by romukena         ###   ########.fr       */
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
	node->argv = NULL;
	node->pipe_out = 0;
	node->redir = NULL;
	node->next = NULL;
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
	node->next = NULL;
	return (node);
}

void add_redir(t_cmd *cmd, t_redir *new)
{
	t_redir *tmp;
	
	tmp = cmd->redir;
	if (!cmd->redir)
	{
		cmd->redir = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void add_arg(t_cmd *cmd, char *arg)
{
	int	i;
	i = 0;
	if (!cmd->argv)
	{
		cmd->argv = malloc(sizeof(char * ) * 1);
		cmd->argv[0] = ft_strdup(arg);
		return ;
	}
	return ;
}