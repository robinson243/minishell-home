/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:45:35 by ydembele          #+#    #+#             */
/*   Updated: 2025/12/06 18:04:14 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	existe(char *str, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!env)
		return (-1);
	while (str[len] && str[len] != '=')
		len++;
	while (env[i])
	{
		if (ft_strncmp(env[i], str, len) == 0
			&& (env[i][len] == '=' || env[i][len] == '\0'))
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
	if (!str)
		return (NULL);
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

int	is_long_long(char *str)
{
	int		neg;
	int		len;

	neg = 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			neg = 1;
		str++;
	}
	while (*str == '0')
		str++;
	len = ft_strlen(str);
	if ((!neg && ft_strcmp(str, "9223372036854775807") > 0)
		|| (neg && ft_strcmp(str, "9223372036854775808") > 0))
		return (0);
	while (isdigit(*str))
		str++;
	if (*str != '\0' || len > 19)
		return (0);
	if (len < 19)
		return (1);
	return (1);
}
