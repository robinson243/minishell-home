/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:56:50 by romukena          #+#    #+#             */
/*   Updated: 2025/04/10 10:42:15 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*in_tab(char *dest, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len;
	char			*dest;

	len = ft_strlen(s1) + ft_strlen(s2);
	dest = (char *)malloc(len + 1);
	if (!dest || !s1 || !s2)
		return (NULL);
	in_tab(dest, s1);
	in_tab(dest + ft_strlen(s1), s2);
	dest[len] = '\0';
	return (dest);
}

/* int main()
{
    // Test 1 : Chaînes non vides
    char *result1 = ft_strjoin("Hello, ", "World!");
    printf("Test 1 : %s\n", result1);  // Attendu : "Hello, World!"
    free(result1);  // N'oublie pas de libérer la mémoire

    // Test 2 : Première chaîne vide
    char *result2 = ft_strjoin("", "World!");
    printf("Test 2 : %s\n", result2);  // Attendu : "World!"
    free(result2);

    // Test 3 : Deuxième chaîne vide
    char *result3 = ft_strjoin("Hello, ", "");
    printf("Test 3 : %s\n", result3);  // Attendu : "Hello, "
    free(result3);

    // Test 4 : Les deux chaînes sont vides
    char *result4 = ft_strjoin("", "");
    printf("Test 4 : %s\n", result4);  // Attendu : ""
    free(result4);

    // Test 5 : Chaînes longues
    char *result5 = ft_strjoin("A long string, ", "with a lot of text.");
    printf("Test 5 : %s\n", result5);  // "A long string, with a lot of text."
    free(result5);


    // Test 7 : Concaténation avec une chaîne vide au milieu
    char *result7 = ft_strjoin("Start", "");
    printf("Test 7 : %s\n", result7);  // Attendu : "Start"
    free(result7);

    return 0;
} */