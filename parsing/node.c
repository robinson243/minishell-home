/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:09:19 by romukena          #+#    #+#             */
/*   Updated: 2025/11/18 17:00:36 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_node	*create_node(char *content, int quoted)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->quoted = quoted;
	node->next = NULL;
	return (node);
}

void	add_node(t_node **head, t_node *new)
{
	t_node	*current;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	clear_nodes(t_node **head)
{
	t_node	*current;
	t_node	*tmp;

	if (*head == NULL)
		return ;
	current = *head;
	while (current)
	{
		tmp = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = tmp;
	}
	*head = NULL;
}

void	print_list(t_node **head)
{
	t_node	*tmp;

	if (!head || !*head)
	{
		printf("(liste vide)\n");
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		printf("le type est %d\n", tmp->type);
		if (tmp->content)
			printf("%s\n", tmp->content);
		else
			printf("(null)\n");
		tmp = tmp->next;
	}
}
