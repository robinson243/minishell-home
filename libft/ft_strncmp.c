/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:26:01 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 12:38:56 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i] && i + 1 < n)
		i++;
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* int main(void) {
    // Cas 1 : chaînes identiques
    // Résultat attendu : 0
    printf("1. \"%s\" vs \"%s\" (n = %d) => %d\n",
           "hello", "hello", 5, ft_strncmp("hello", "hello", 5));

    // Cas 2 : dernières lettres différentes ('o' > 'a')
    // Résultat attendu : positif (ex: 'o' - 'a' = 111 - 97 = 14)
    printf("2. \"%s\" vs \"%s\" (n = %d) => %d\n",
           "hello", "hella", 5, ft_strncmp("hello", "hella", 5));

    // Cas 3 : on compare que les 4 premiers caractères ("hell")
    // Résultat attendu : 0 (car "hell" == "hell")
    printf("3. \"%s\" vs \"%s\" (n = %d) => %d\n",
           "hello", "hella", 4, ft_strncmp("hello", "hella", 4));

    // Cas 4 : une chaîne plus courte (hi\0 vs hijac...)
    // Résultat attendu : négatif (car '\0' < 'j')
    printf("4. \"%s\" vs \"%s\" (n = %d) => %d\n",
           "hi", "hijack", 5, ft_strncmp("hi", "hijack", 5));

    // Cas 5 : caractères nuls internes ("he\0llo" vs "he\0p")
    // Résultat attendu : négatif (car 'l' < 'p' après '\0' mais non comparé)
    // En réalité : on s'arrête à "he" donc '\0' == '\0' => 0
    printf("5. \"he\\0llo\" vs \"he\\0p\" (n = %d) => %d\n",
           5, ft_strncmp("he\0llo", "he\0p", 5));

    // Cas 6 : une chaîne vide
    // Résultat attendu : négatif ('' < 'a')
    printf("6. \"%s\" vs \"%s\" (n = %d) => %d\n",
           "", "abc", 3, ft_strncmp("", "abc", 3));

    // Cas 7 : deux chaînes vides
    // Résultat attendu : 0
    printf("7. \"%s\" vs \"%s\" (n = %d) => %d\n",
           "é", "a", 2, ft_strncmp("", "", 2));

    // Cas 8 : n = 0 → ne compare rien
    // Résultat attendu : 0
    printf("8. \"%s\" vs \"%s\" (n = %d) => %d\n",
           "abc", "def", 0, ft_strncmp("abc", "def", 0));

    return 0;
} */