/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 00:52:10 by romukena          #+#    #+#             */
/*   Updated: 2025/04/15 02:36:09 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/* 
int main(void) {
    t_list *list = NULL;

    t_list *node1 = ft_lstnew("World");
    t_list *node2 = ft_lstnew("Hello");

    ft_lstadd_front(&list, node1);
    ft_lstadd_front(&list, node2);

    // Affiche la liste pour vérifier l’ordre
    t_list *tmp = list;
    while (tmp) {
        printf("%s\n", (char *)tmp->content);
        tmp = tmp->next;
    }

    // Libération (optionnelle ici)
    free(node1);
    free(node2);

    return 0;
} */