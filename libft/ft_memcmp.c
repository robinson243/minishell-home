/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 17:18:15 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 12:26:45 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = s1;
	str2 = s2;
	i = 0;
	if (n <= 0)
		return (0);
	while ((i < n - 1) && str1[i] == str2[i])
	{
		i++;
	}
	return (str1[i] - str2[i]);
}
/* int main() {
	char myStr1[] = "ABCe";
	char myStr2[] = "ABCE";
	int cmp = ft_memcmp(myStr1, myStr2, 2);
	int cmp1 = memcmp(myStr1, myStr2, 2);
	printf("str1 : %s; str2 : %s ; ", myStr1, myStr2);
	printf("difference is %d | %d\n", cmp, cmp1) ;

	printf(" le res %d", ft_memcmp("abcdefghij", "abcdefgxyz", 7));
	return 0;
  } */