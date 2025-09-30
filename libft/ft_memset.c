/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 01:13:29 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 12:33:17 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = s;
	i = 0;
	while (i < n)
		ptr[i++] = (char)c;
	return (ptr);
}
/* 
int main()
{
    int length;

    // Test pour un tableau de caractères
    char str[] = "hello";
    size_t size = 0;
    printf("Initial string: ");
    for (length = 0; length < 5; length++) {
        printf("%c ", str[length]);
    }
    printf("\n");

    ft_memset(str, 'l', size);

    
    printf("\nAfter memset:\n");
    printf("Modified string: ");
    for (length = 0; length < 5; length++) {
        printf("%c ", str[length]);
    }
    printf("\n");

    return 0;
} */