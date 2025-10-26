/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:45:27 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/19 18:07:13 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	s_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
	{
		if (s2[i + 1] && s2[i + 1] == '=')
			break ;
		i++;
	}
	return (s1[i] - s2[i]);
}

int	existe(char *str, char **env)
{
	int	i;

	i = 0;

	while (env[i])
	{
		if (s_cmp(str, env[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**export(int i, char **env, char *str)
{
	char	**new_env;
	int		j;
	int		l;

	l = 0;
	j = 0;
	if (i >= 0)
		new_env = malloc (sizeof(char *) * (len(env) + 1));
	else
		new_env = malloc (sizeof(char *) * (len(env) + 2));
	if (!new_env)
		return (NULL);
	while (env[l])
	{
		if (j != i)
		{
			new_env[j] = ft_strdup(env[l]);
			if (!new_env[j])
				return (free_all(new_env), NULL);
			l++;
		}
		else
		{
			new_env[j] = ft_strdup(str);
			if (!new_env[j])
				return (free_all(new_env), NULL);
		}
		j++;
	}
	if (i == -1)
	{
		new_env[j] = ft_strdup(env[i]);
		if (!new_env[j++])
			return (free_all(new_env), NULL);
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**ft_export(char **cmd, char	**env)
{
	int		i;
	char	**new_env;

	i = 1;
	new_env = NULL;
	if (!cmd[1])
		export_noargs(env);
	while (cmd[i])
	{
		free_all(new_env);
		if (invalide_arg(cmd[i]))
			return (2);
		new_env = export(existe(cmd[i], env), env, cmd[i]);
		if (!new_env)
			return (perror("malloc :"), env);
		i++;
	}
	if (new_env == NULL)
		return (NULL);
	// free_all(env); // dupliquer le env sinon segfault
	return (new_env);
}
