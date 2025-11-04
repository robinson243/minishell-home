/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:45:35 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/04 13:48:13 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	existe(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0 &&
			(env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	**ft_strdupdup(char **str)
{
	char	**res;
	int		i;

	i = 0;
	res = NULL;
	res = malloc(sizeof(char *) * (len_list(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = ft_strdup(str[i]);
		if (!res[i])
		{
			free_all(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	ft_swap(int i, int j, char **tab)
{
	char	*temp;

	temp = tab[i];
	tab[i] = tab[j];
	tab[j] = temp;
}

int	len_list(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

