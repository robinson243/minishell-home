/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:45:27 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/13 15:53:23 by ydembele         ###   ########.fr       */
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
		if (!ft_isalnum(str[i]) && str[i] != '_')
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

char	**export(int pos, char **env, char *str)
{
	char	**new_env;
	int		size;
	int		i;

	size = len_list(env);
	if (pos != -1)
	{
		new_env = ft_strdupdup(env);
		if (!new_env)
			return (NULL);
		free(new_env[pos]);
		new_env[pos] = ft_strdup(str);
		free_all(env);
		return (new_env);
	}
	new_env = malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_all(new_env), NULL);
	}
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free_all(env);
	return (new_env);
}

char	**ft_export(char **cmd, char **env, t_cmd *command, t_exec *exec)
{
	int		i;
	char	**new_env;

	(void)command;
	i = 1;
	if (!cmd[1])
		return (export_noargs(env), env);
	while (cmd[i])
	{
		if (!invalide_arg(cmd[i]))
		{
			write(2, "export: invalid identifier\n", 28);
			exec->exit_code = 1;
		}
		else
		{
			new_env = export(existe(cmd[i], env), env, cmd[i]);
			if (!new_env)
			{
				exec->exit_code = 1;
				perror("Malloc");
				return (env);
			}
			env = new_env;
		}
		i++;
	}
	return (env);
}
