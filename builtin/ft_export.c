/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:45:27 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/20 13:53:32 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

char	**export_update(int pos, char **env, char *str)
{
	char	**new_env;

	new_env = ft_strdupdup(env);
	if (!new_env)
		return (NULL);
	free(new_env[pos]);
	new_env[pos] = ft_strdup(str);
	if (!new_env[pos])
	{
		free_all(new_env);
		return (NULL);
	}
	free_all(env);
	return (new_env);
}

char	**export_add(char **env, char *str)
{
	char	**new_env;
	int		size;
	int		i;

	size = len_list(env);
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
	new_env[i] = ft_strdup(str);
	if (!new_env[i])
		return (free_all(new_env), NULL);
	i++;
	new_env[i] = NULL;
	free_all(env);
	return (new_env);
}

char	**export(int pos, char **env, char *str)
{
	if (pos != -1)
		return (export_update(pos, env, str));
	return (export_add(env, str));
}

char	**do_export(char *arg, char **env, t_exec *exec)
{
	char	**new_env;
	char	*normalized;

	if (!invalide_arg(arg))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		exec->exit_code = 1;
		return (env);
	}
	normalized = normalize_export_arg(arg);
	if (!normalized)
	{
		exec->exit_code = 1;
		return (perror("Malloc"), env);
	}
	new_env = export(existe(normalized, env), env, normalized);
	if (!new_env)
	{
		exec->exit_code = 1;
		perror("Malloc");
		return (free(normalized), env);
	}
	return (free(normalized), new_env);
}

char	**ft_export(char **cmd, char **env, t_exec *exec)
{
	int		i;

	i = 1;
	if (!cmd[1])
	{
		exec->exit_code = export_noargs(env);
		return (env);
	}
	while (cmd[i])
	{
		env = do_export(cmd[i], env, exec);
		i++;
	}
	return (env);
}
