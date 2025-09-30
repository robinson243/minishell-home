/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:55:18 by romukena          #+#    #+#             */
/*   Updated: 2025/04/15 02:27:49 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

/* int main(void)
{
    char *str = "Hello, world!";
    t_list *node = ft_lstnew(str);

    if (node == NULL)
    {
        printf("Erreur : allocation échouée\n");
        return 1;
    }

    printf("Content : %s\n", (char *)node->content);
    printf("Next : %p\n", node->next);

    return 0;
} */