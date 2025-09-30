/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:00:49 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 12:23:53 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*buf_char;

	buf_char = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (buf_char[i] == (unsigned char)c)
		{
			return (buf_char + i);
		}
		i++;
	}
	return (NULL);
}

/* int	main(void)
{
	const char str1[] = "hello world";
	const char str2[] = "42 is cool";
	const char str3[] = "banana";
	void *res;

	// Test 1 — caractère trouvé
	res = ft_memchr(str1, 'w', 11);
	if (res)
		printf("Test 1: Found '%c' at offset %ld\n",
			*(char *)res, (char *)res - (char *)str1);
	else
		printf("Test 1: NULL (not found)\n");

	// Test 2 — caractère absent
	res = ft_memchr(str2, 'z', 10);
	if (res)
		printf("Test 2: Found '%c' at offset %ld\n",
			*(char *)res, (char *)res - (char *)str2);
	else
		printf("Test 2: NULL (not found)\n");

	// Test 3 — plusieurs occurrences
	res = ft_memchr(str3, 'a', 6);
	if (res)
		printf("Test 3: Found '%c' at offset %ld\n",
			*(char *)res, (char *)res - (char *)str3);
	else
		printf("Test 3: NULL (not found)\n");

	return (0);
} */