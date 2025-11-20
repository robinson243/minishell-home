/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:58:58 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/20 13:17:11 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	invalide_arg(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_' && !(str[i] == '+'
				&& (str[i + 1] && str[i + 1] == '=')))
			return (0);
		i++;
	}
	return (1);
}

void	sort_env(char **env, int len)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strncmp(env[i], env[j], INT_MAX) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int	export_noargs(char **env)
{
	char	**arr;
	int		i;
	int		j;

	arr = ft_strdupdup(env);
	if (!arr)
		return (1);
	sort_env(arr, len_list(env));
	i = 0;
	while (arr[i])
	{
		printf("export ");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free_all(arr);
	return (0);
}

void	lst_clear(t_redir **lst)
{
	t_redir	*current;
	t_redir	*data_next;

	current = *lst;
	if (!*lst)
		return ;
	while (current)
	{
		data_next = current->next;
		free(current->file);
		free(current);
		current = data_next;
	}
	*lst = NULL;
}

char	*normalize_export_arg(char *arg)
{
	char	*eq;
	char	*res;

	eq = ft_strchr(arg, '=');
	if (eq)
		return (ft_strdup(arg));
	res = malloc(ft_strlen(arg) + 4);
	if (!res)
		return (NULL);
	strcpy(res, arg);
	ft_strlcat(res, "=\"\"", ft_strlen(res) + 2);
	return (res);
}
