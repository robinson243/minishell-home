/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 20:30:43 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 00:28:34 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	char	alpha;

	alpha = (char)c;
	if (ft_isdigit(alpha) || ft_isalpha(alpha))
		return (1);
	return (0);
}

/* int	main(void)
{
	// Quelques cas de test
	char tests[] = {'a', 'Z', '5', ' ', '@', '\n', 'm', '0', '9', '#'};
	int i;

	printf("Test de ft_isalnum:\n");
	for (i = 0; i < (int)(sizeof(tests) / sizeof(tests[0])); i++)
	{
		char c = tests[i];
		int result = ft_isalnum(c);
		printf("ft_isalnum('%c' | ASCII %d) = %d\n", c, c, result);
	}
	return (0);
} */