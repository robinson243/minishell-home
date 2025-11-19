/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dems <dems@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:53:29 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/19 10:47:29 by dems             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// int	exist(char **path, t_cmd *command, t_globale *data, t_exec *exec)
// {
// 	if (access(command->argv[0], F_OK) == 0)
// 	{
// 		*path = ft_strdup(command->argv[0]);
// 		if (!(*path))
// 			exec->exit_code = 1;
// 	}
// 	else
// 		*path = get_path(data->env, command->argv[0], command, exec);
// 	if (!(*path) && exec->exit_code == 1)
// 		free_exit(data, "Malloc", 1);
// 	if (!(*path))
// 	{
// 		exec->exit_code = 127;
// 		write(2, command->argv[0], ft_strlen(command->argv[0]));
// 		write(2, ": command not found\n", 21);
// 		return (0);
// 	}
// 	if (access((*path), X_OK))
// 	{
// 		exec->exit_code = 126;
// 		return (perror(*path), free((*path)), 0);
// 	}
// 	if (!check_dir(path, command->argv[0], command, exec))
// 		return (0);
// 	return (1);
// }


int	exist(char **path, t_cmd *command, t_globale *data, t_exec *exec)
{
	int			has_slash;

	has_slash = (ft_strchr(command->argv[0], '/') != NULL);
	if (access(command->argv[0], F_OK) == 0)
	{
		*path = ft_strdup(command->argv[0]);
		if (!(*path))
			exec->exit_code = 1;
	}
	else
		*path = get_path(data->env, command->argv[0], exec);
	if (!(*path) && exec->exit_code == 1)
		free_exit(data, "Malloc", 1);
	if (!(*path))
	{
		exec->exit_code = 127;
		write(2, command->argv[0], ft_strlen(command->argv[0]));
		write(2, ": command not found\n", 21);
		return (0);
	}
	if (check_dir(path, command->argv[0], command, exec) == 0)
		return (0);
	if (access(*path, X_OK) != 0)
	{
		if (has_slash)
		{
			exec->exit_code = 126;
			perror(*path);
		}
		else
		{
			exec->exit_code = 127;
			write(2, command->argv[0], ft_strlen(command->argv[0]));
			write(2, ": command not found\n", 21);
		}
		free(*path);
		return (0);
	}
	return (1);
}

char	**remp_local(char **env, t_exec *exec)
{
	int		i;
	char	**local;

	i = 0;
	local = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH=", env[i], 5) == 0)
		{
			local = ft_split(env[i] + 5, ':');
			if (!local)
				exec->exit_code = 1;
		}
		i++;
	}
	return (local);
}

char	*get_path(char **env, char *cmd, t_exec *exec)
{
	int		i;
	char	**local;
	char	*path;

	i = 0;
	local = remp_local(env, exec);
	if (!local)
		return (NULL);
	while (local[i])
	{
		path = ft_strslashjoin(local[i], cmd);
		if (!path)
		{
			exec->exit_code = 1;
			return (free_all(local), NULL);
		}
		if (access(path, X_OK) == 0)
			return (free_all(local), path);
		free(path);
		i++;
	}
	free_all(local);
	return (NULL);
}

int	check_dir(char **path, char *cmd, t_cmd *command, t_exec *exec)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	(void)command;
	if (!S_ISREG(path_stat.st_mode))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, " : Is a directory\n", 19);
		free(*path);
		exec->exit_code = 126;
		return (0);
	}
	return (1);
}
