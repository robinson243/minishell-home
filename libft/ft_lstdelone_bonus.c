/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:50:11 by romukena          #+#    #+#             */
/*   Updated: 2025/04/15 15:55:51 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/* void	del(void *content)
{
	if (content)
		free(content);
}
int	main(void)
{
	// Création d'un maillon
	t_list	*node = malloc(sizeof(t_list));
	if (!node)
		return (1);

	// Allocation et affectation du content
	char *str = malloc(20);
	if (!str)
	{
		free(node);
		return (1);
	}
	strcpy(str, "Hello, World!");

	node->content = str;
	node->next = NULL;

	printf("Avant ft_lstdelone : %s\n", (char *)node->content);

	// Suppression du maillon
	ft_lstdelone(node, del);

	printf("Après ft_lstdelone : maillon supprimé\n");

	return (0);
} */