/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:53:29 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/19 15:55:09 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exist(char *cmd, char **path, t_globale *data)
{
	if (access(cmd, F_OK) == 0)
	{
		*path = ft_strdup(cmd);
		if (!(*path))
			data->exit_code = 1;
	}
	else
		*path = get_path(data->env, cmd, data);
	if (!(*path) && data->exit_code == 1)
		free_exit(data, "Malloc", 1);
	if (!(*path))
	{
		data->exit_code = 127;
		return (0);
	}
	if (access((*path), X_OK))
	{
		data->exit_code = 126;
		return (perror(*path), free((*path)), 0);
	}
	if (!check_dir(path, cmd, data))
		return (0);
	return (1);
}

char	*get_path(char **env, char *cmd, t_globale *data)
{
	int		i;
	char	**local;
	char	*path;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			local = ft_split(env[i] + 5, ':');
			if (!local)
				data->exit_code = 1;
		}
		i++;
	}
	i = 0;
	if (!local)
		return (0);
	while (local[i])
	{
		path = ft_strslashjoin(local[i++], cmd);
		if (!path)
		{
			data->exit_code = 1;
			return (free_all(local), NULL);
		}
		if (access(path, F_OK) == 0)
			return (free_all(local), path);
		free(path);
	}
	return (free_all(local), NULL);
}

int	check_dir(char **path, char *cmd, t_globale *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, " : Is a directory\n", 19);
		data->exit_code = 126;
		return (0);
	}
	return (1);
}

