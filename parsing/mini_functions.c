/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:13:06 by romukena          #+#    #+#             */
/*   Updated: 2025/10/29 16:22:29 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*mini_double_quoted(char *input, int *i, int *quoted)
{
	char	*tmp;

	tmp = extract_quoted(input, i);
	*quoted = 1;
	return (tmp);
}

char	*mini_single_quoted(char *input, int *i, int *quoted)
{
	char	*tmp;

	tmp = extract_single_quoted(input, i);
	*quoted = 2;
	return (tmp);
}
