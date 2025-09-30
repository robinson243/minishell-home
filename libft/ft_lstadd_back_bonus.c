/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 04:43:31 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 17:56:27 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

/* 
int main(void) {
    t_list *list = NULL;

    // Création de quelques éléments
    t_list *node1 = ft_lstnew("Premier");
    t_list *node2 = ft_lstnew("Deuxième");
    t_list *node3 = ft_lstnew("Troisième");

    // Chaînage des éléments
    list = node1;
    node1->next = node2;
    node2->next = node3;

    // Nouveau nœud à ajouter à la fin
    t_list *node4 = ft_lstnew("Quatrième");

    // Appel de la fonction pour ajouter à la fin de la liste
    ft_lstadd_back(&list, node4);

    t_list *current = list;
    while (current != NULL) {
        printf("%s -> ", (char *)current->content);
        current = current->next;
    }
    printf("NULL\n");

    // Libération mémoire (optionnel ici)
    free(node1);
    free(node2);
    free(node3);
    free(node4);

    return 0;
} */