/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:32:49 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 15:13:23 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_len(long int nb)
{
	int	i;

	i = 0;
	if (nb <= 0)
	{
		i++;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*dest;
	int			len;
	long int	nb;

	nb = n;
	len = count_len(nb);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	if (nb == 0)
		dest[0] = '0';
	dest[len] = '\0';
	if (nb < 0)
	{
		nb = -nb;
		dest[0] = '-';
	}
	while (nb > 0)
	{
		dest[--len] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (dest);
}

/* int	main(void)
{
	printf("%s\n", ft_itoa(-15545));
} */