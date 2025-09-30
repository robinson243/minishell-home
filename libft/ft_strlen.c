/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 00:35:10 by romukena          #+#    #+#             */
/*   Updated: 2025/09/30 15:12:37 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*end;

	end = s;
	if (!s)
		return (0);
	while (*end)
		end++;
	return (end - s);
}
/* int main(void)
{
	const char *str = "HELLO";
	size_t val = ft_strlen(str);

	printf("%ld", val);
} */
