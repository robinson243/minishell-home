/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:53:29 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/03 16:08:07 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exist(char *cmd, char **path, t_cmd *command, t_globale *data)
{
	if (access(cmd, F_OK) == 0)
	{
		*path = ft_strdup(cmd);
		if (!(*path))
			command->exit_code = 1;
	}
	else
		*path = get_path(data->env, cmd, command);
	if (!(*path) && command->exit_code == 1)
		free_exit(data, "Malloc", 1);
	if (!(*path))
	{
		command->exit_code = 127;
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 21);
		return (0);
	}
	if (access((*path), X_OK))
	{
		command->exit_code = 126;
		return (perror(*path), free((*path)), 0);
	}
	if (!check_dir(path, cmd, command))
		return (0);
	return (1);
}

char	*get_path(char **env, char *cmd, t_cmd *command)
{
	int		i;
	char	**local;
	char	*path;

	i = 0;
	local = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			local = ft_split(env[i] + 5, ':');
			if (!local)
				command->exit_code = 1;
		}
		i++;
	}
	i = 0;
	if (!local)
		return (NULL);
	while (local[i])
	{
		path = ft_strslashjoin(local[i++], cmd);
		if (!path)
		{
			command->exit_code = 1;
			return (free_all(local), NULL);
		}
		if (access(path, F_OK) == 0)
			return (free_all(local), path);
		free(path);
	}
	return (free_all(local), NULL);
}

int	check_dir(char **path, char *cmd, t_cmd *command)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, " : Is a directory\n", 19);
		free(*path);
		command->exit_code = 126;
		return (0);
	}
	return (1);
}

