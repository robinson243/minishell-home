/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:16:28 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 16:16:45 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*data_next;

	current = *lst;
	if (!*lst || !del)
		return ;
	while (current)
	{
		data_next = current->next;
		del(current->content);
		free(current);
		current = data_next;
	}
	*lst = NULL;
}
/* 
void	del(void *content)
{
	free(content);
}

int	main(void)
{
	// Création de 3 maillons
	t_list *node1 = malloc(sizeof(t_list));
	t_list *node2 = malloc(sizeof(t_list));
	t_list *node3 = malloc(sizeof(t_list));
	if (!node1 || !node2 || !node3)
		return (1);
	node1->content = strdup("Hello");
	node1->next = node2;
	node2->content = strdup("World");
	node2->next = node3;
	node3->content = strdup("42");
	node3->next = NULL;

	// Affichage avant appel de ft_lstclear
	printf("Avant ft_lstclear :\n");
	t_list *temp = node1;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}

	// Appel de ft_lstclear
	ft_lstclear(&node1, del);

	// Affichage après appel de ft_lstclear
	printf("Après ft_lstclear :\n");
	if (node1 == NULL)
	{
		printf("Liste libérée et pointeur à NULL ✅\n");
	}
	else
	{
		printf("Problème, le pointeur n'est pas NULL ❌\n");
	}

	return (0);
} */