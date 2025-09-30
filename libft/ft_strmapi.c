/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:53:05 by romukena          #+#    #+#             */
/*   Updated: 2025/04/13 03:26:04 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int		i;
	char				*dest;

	i = 0;
	dest = (char *)malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[ft_strlen(s)] = '\0';
	return (dest);
}

/* char to_upper_if_even(unsigned int i, char c)
{
    if (i % 2 == 0 && c >= 'a' && c <= 'z')
        return c - 32; // Convertit en majuscule
    return c;
}

int main(void)
{
    char *str = "hello world";
    char *result = ft_strmapi(str, to_upper_if_even);

    if (result)
    {
        printf("Résultat : %s\n", result);
        free(result);
    }
    else
    {
        printf("Erreur d'allocation mémoire.\n");
    }

    return 0;
} */