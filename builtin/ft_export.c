/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:45:27 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/03 16:11:52 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	invalide_arg(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	sort_env(char **env, int len)
{
	int	i;
	int	j;
	int	diff;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			diff = ft_strncmp(env[i], env[j], __INT_MAX__);
			if (diff > 0)
			{
				ft_swap(i, j, env);
				continue ;
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
		printf("export");
		j = 0;
		while (arr[i][j] && arr[i][j] != '=')
			printf("%c", arr[i][j++]);
		if (arr[i][j] && arr[i][j] == '=')
			printf("=\"%s\"\n", &arr[i][j + 1]);
		else
			printf("\n");
		i++;
	}
	free_all(arr);
	return (0);
}

char	**export(int pos, char **env, char *str)
{
	char	**new_env;
	int		size;
	int		i;

	i = 0;
	size = len_list(env);
	if (pos != -1)
	{
		new_env = ft_strdupdup(env);
		if (!new_env)
			return (NULL);
		free(new_env[pos]);
		new_env[pos] = strdup(str);
		return (new_env);
	}
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	while (i < size)
	{
		new_env[i] = strdup(env[i]);
		if (!new_env[i])
			return (free_all(new_env), NULL);
		i++;
	}
	new_env[i++] = strdup(str);
	new_env[i] = NULL;
	return (new_env);
}

char	**ft_export(char **cmd, char **env, t_cmd *command)
{
	int		i;
	char	**new_env;

	i = 1;
	new_env = NULL;
	if (!cmd[1])
		export_noargs(env);
	while (cmd[i])
	{
		if (!invalide_arg(cmd[i]))
		{
			write(2, "export: invalid identifier\n", 28);
			command->exit_code = 1;
			i++;
			continue ;
		}
		new_env = export(existe(cmd[i], env), env, cmd[i]);
		if (!new_env)
			return (perror("malloc :"), env);
		free_all(env);
		env = new_env;
		i++;
	}
	return (new_env);
}

