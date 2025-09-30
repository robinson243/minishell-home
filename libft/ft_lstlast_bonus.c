/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 03:25:19 by romukena          #+#    #+#             */
/*   Updated: 2025/04/15 04:40:32 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/* int main(void) {
    t_list *list = NULL;

    t_list *node1 = ft_lstnew("Premier");
    t_list *node2 = ft_lstnew("Deuxième");
    t_list *node3 = ft_lstnew("Dernier");

    // Chaînage des éléments
    node1->next = node2;
    node2->next = node3;
    list = node1;

    // Appel de la fonction à tester
    t_list *last = ft_lstlast(list);

    if (last)
        printf("Contenu du dernier élément : %s\n", (char *)last->content);
    else
        printf("La liste est vide.\n");

    // Libération mémoire (optionnel ici)
    free(node1);
    free(node2);
    free(node3);

    return 0;
} */