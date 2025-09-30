/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 10:44:39 by romukena          #+#    #+#             */
/*   Updated: 2025/04/20 02:34:21 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_set(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_set(set, s1[start]))
		start++;
	while (s1[end - 1] && is_set(set, s1[end - 1]))
		end--;
	if (start >= end)
		return (ft_strdup(""));
	dest = (char *)malloc(end - start + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (i < (end - start))
	{
		dest[i] = s1[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/* int	main(void)
{
	char *res;

	// Test 1 : espaces autour
	res = ft_strtrim("   Hello World   ", " ");
	printf("1: [%s]\n", res); // attendu : [Hello World]
	free(res);

	// Test 2 : 'x' autour mais pas au milieu
	res = ft_strtrim("xxx42xxxNetworkxx", "x");
	printf("2: [%s]\n", res); // attendu : [42xxxNetwork]
	free(res);

	// Test 3 : '!' au début et à la fin uniquement
	res = ft_strtrim("!!Salut!!ça va!!", "!");
	printf("3: [%s]\n", res); // attendu : [Salut!!ça va]
	free(res);

	// Test 4 : rien à supprimer
	res = ft_strtrim("Pas de trims", "x");
	printf("4: [%s]\n", res); // attendu : [Pas de trims]
	free(res);

	// Test 5 : chaîne vide
	res = ft_strtrim("", " \n\t");
	printf("5: [%s]\n", res); // attendu : []
	free(res);

	// Test 6 : tout à supprimer
	res = ft_strtrim("xxxx", "x");
	printf("6: [%s]\n", res); // attendu : []
	free(res);

	// Test 7 : set vide
	res = ft_strtrim("test", "");
	printf("7: [%s]\n", res); // attendu : [test]
	free(res);

	// Test 8 : string vide + set vide
	res = ft_strtrim("", "");
	printf("8: [%s]\n", res); // attendu : []
	free(res);

	res = ft_strtrim("lorem ipsum dolor sit amet", "te");
	printf("9: [%s]\n", res); // attendu : []
	free(res);

	return (0);
} */