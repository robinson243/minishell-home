/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:28:09 by romukena          #+#    #+#             */
/*   Updated: 2025/04/30 12:59:20 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_char;
	unsigned char	*dest_char;
	size_t			len;

	i = 0;
	src_char = (unsigned char *)src;
	dest_char = (unsigned char *)dest;
	if (dest_char > src_char && dest_char < src_char + n)
	{
		len = n;
		while (len-- > 0)
			dest_char[len] = src_char[len];
	}
	else
	{
		while (i < n)
		{
			dest_char[i] = src_char[i];
			i++;
		}
	}
	return (dest_char);
}

/* void	print_result(const char *label, const char *exp, char *got, int size)
{
	printf("%s:\n", label);
	write(1, "→ Résultat   : ", 16);
	write(1, got, size);
	write(1, "\n→ Attendu    : ", 16);
	write(1, exp, size);
	write(1, "\n\n", 2);
}

int	main(void)
{
	char test1[20] = "abcdefghij";
	char test2[20] = "abcdefghij";

	// ✅ Test 1 : Sans chevauchement
	char buffer1[20] = "XXXXXXXXXX";
	char buffer2[20] = "XXXXXXXXXX";
	ft_memmove(buffer1, test1, 5);
	memmove(buffer2, test2, 5);
	print_result("Test 1 - Sans chevauchement", buffer2, buffer1, 10);

	// ❌ Test 2 : Chevauchement vers l'avant (dest > src)
	char buffer3[30] = "lorem ipsum dolor sit amet";
	char buffer4[30] = "lorem ipsum dolor sit amet";
	ft_memmove(buffer3 + 7, buffer3, 10);     // copie dans une zone plus loin
	memmove(buffer4 + 7, buffer4, 10);
	print_result("Test 2 - Chevauchement (avant)", buffer4, buffer3, 25);

	// ✅ Test 3 : Chevauchement vers l’arrière (dest < src)
	char buffer5[30] = "1234567890ABCDEF";
	char buffer6[30] = "1234567890ABCDEF";
	ft_memmove(buffer5, buffer5 + 4, 10);
	memmove(buffer6, buffer6 + 4, 10);
	print_result("Test 3 - Chevauchement (arrière)", buffer6, buffer5, 16);

	// ✅ Test 4 : Vérifie adresse de retour
	char test_dest[10] = "---------";
	char *ret = ft_memmove(test_dest, "data!!!", 5);
	if (ret == test_dest)
		printf("Test 4 - Adresse de retour : ✅ OK\n\n");
	else
		printf("Test 4 - Adresse de retour : ❌ NOK\n\n");

	return (0);
} */