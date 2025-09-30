/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:50:48 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 00:19:16 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	char	letter;

	letter = (char)c;
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z' ))
		return (1);
	return (0);
}

/* int main(void)
{
	printf("%d", ft_isalpha('m'));
} */