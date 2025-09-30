/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:07:48 by romukena          #+#    #+#             */
/*   Updated: 2025/04/16 14:16:29 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/* void print_content(void *content)
{
    printf("%s\n", (char *)content);
}

// Fonction pour créer un nouvel élément de liste
t_list *new_node(char *str)
{
    t_list *node = malloc(sizeof(t_list));
    if (!node)
        return NULL;
    node->content = str;
    node->next = NULL;
    return node;
}

int main(void)
{
    // Création de la liste : "Un" -> "Deux" -> "Trois"
    t_list *a = new_node("Un");
    t_list *b = new_node("Deux");
    t_list *c = new_node("Trois");

    a->next = b;
    b->next = c;

    // Test de ft_lstiter
    ft_lstiter(a, &print_content);

    // Libération manuelle si nécessaire après les tests
    free(a);
    free(b);
    free(c);

    return 0;
} */