/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:21:01 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 12:35:23 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	*buffer;

	i = 0;
	buffer = (unsigned char *)s;
	while (buffer[i])
	{
		if (buffer[i] == (char)c)
			return ((char *)buffer + i);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)buffer + i);
	return (NULL);
}

/* int main ()
{
  char str[] = "This is a sample string";
  char * pch;
  pch=ft_strchr(str,'s');
  printf("%s", pch);
  return 0;
} */