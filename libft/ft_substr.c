/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 08:18:14 by romukena          #+#    #+#             */
/*   Updated: 2025/04/28 23:48:08 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* int main(void)
{
	char *s;
    char *result;

    // Test 1
	s = "";
    result = ft_substr(s, 0, 5);
    printf("Test 8 : %s\n", result); // attendu : (chaîne vide)
    free(result);

    // Test 9 : chaîne d’un seul caractère, len = 1
    s = "X";
    result = ft_substr(s, 0, 1);
    printf("Test 9 : %s\n", result); // attendu : X
    free(result);

    // Test 10 : chaîne d’un seul caractère, len = 2
    s = "Y";
    result = ft_substr(s, 0, 2);
    printf("Test 10 : %s\n", result); // attendu : Y
    free(result);

    // Test 11 : start à 1, len = 1, sur une chaîne de 2 lettres
    s = "AB";
    result = ft_substr(s, 1, 1);
    printf("Test 11 : %s\n", result); // attendu : B
    free(result);

    // Test 12 : start = 0, len = strlen
    s = "Complete";
    result = ft_substr(s, 0, 8);
    printf("Test 12 : %s\n", result); // attendu : Complete
    free(result);

    // Test 13 : start = 2, len = 0
    s = "Zero";
    result = ft_substr(s, 2, 0);
    printf("Test 13 : %s\n", result); // attendu : (chaîne vide)
    free(result);

    // Test 14 : start = 0, len = 0 sur chaîne vide
    s = "";
    result = ft_substr(s, 0, 0);
    printf("Test 14 : %s\n", result); // attendu : (chaîne vide)
    free(result);

    return 0;
} */