/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:52:16 by romukena          #+#    #+#             */
/*   Updated: 2025/04/08 12:02:43 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}

/* int main(void)
{
	printf("%d\n", ft_isascii('e'));   // 1
	printf("%d\n", ft_isascii('é'));   // 0 (non-ASCII)
	printf("%d\n", ft_isascii(128));   // 0
	printf("%d\n", ft_isascii(0));     // 1
	printf("%d\n", ft_isascii(127));   // 1
} */