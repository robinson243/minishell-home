/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:44:27 by romukena          #+#    #+#             */
/*   Updated: 2025/04/15 04:59:30 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	if (lst == NULL)
		return (count);
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

/* int main(void) {
    t_list *list = NULL;

    // Création de quelques éléments
    t_list *node1 = ft_lstnew("un");
    t_list *node2 = ft_lstnew("deux");
    t_list *node3 = ft_lstnew("trois");

    // Construction de la liste
    node1->next = node2;
    node2->next = node3;
    list = node1;

    // Test de ta fonction ft_lstsize
    int size = ft_lstsize(list);
    printf("Taille de la liste : %d\n", size);  // Doit afficher 3

    // Libération (optionnelle ici)
    free(node1);
    free(node2);
    free(node3);

    return 0;
} */