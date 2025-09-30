/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 04:26:12 by romukena          #+#    #+#             */
/*   Updated: 2025/04/19 16:23:18 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <bsd/string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;

	len_dst = ft_strlen(dst);
	i = 0;
	if (size == 0 || size <= len_dst)
		return (size + ft_strlen(src));
	while (i < size - 1 - len_dst && src[i])
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + ft_strlen(src));
}
/* int main(void)
{
	char myStr[20] = "Hello";
	char mystr1[20] = "Hello";
	size_t nb = ft_strlcat(myStr, " World!", 25);
	size_t nb1 = strlcat(mystr1, " World!", 25);
	printf("%s\n", myStr);
	printf("la val : %ld\n",nb);
	printf("---------- \n");
	printf("%s\n", myStr);
	printf("la val : %ld",nb);
	
}  */