/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:53:29 by ydembele          #+#    #+#             */
/*   Updated: 2025/12/06 18:02:28 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	exist(char **path, t_cmd *command, t_globale *data, t_exec *exec)
{
	*path = NULL;
	if (ft_strchr(command->argv[0], '/'))
		*path = ft_strdup(command->argv[0]);
	else
		*path = get_path(data->env, command->argv[0], data->exec);
	if (!*path || (!command->argv[0][0] || (command->argv[0][0] == '.'
		&& (!command->argv[0][1] || (command->argv[0][1] == '.'
		&& !command->argv[0][2])))))
	{
		ft_putstr_fd(command->argv[0], 2);
		exec->exit_code = 127;
		if (*path)
			free(*path);
		return (ft_putstr_fd(": command not found\n", 2), 0);
	}
	if (!check_dir(path, command->argv[0], exec))
		return (free(*path), 0);
	if (access(*path, X_OK) != 0)
	{
		exec->exit_code = 126;
		return (perror(*path), free(*path), 0);
	}
	return (1);
}

char	**remp_local(char **env, t_exec *exec)
{
	int		i;
	char	**local;

	i = 0;
	local = NULL;
	if (!env)
		return (NULL);
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
	if (!local && exec->exit_code == 1)
		return (NULL);
	else if (!local && exec->exit_code == 0)
		return (ft_strdup(cmd));
	while (local[i])
	{
		path = ft_strslashjoin(local[i], cmd);
		if (!path)
		{
			exec->exit_code = 1;
			return (free_all(local), NULL);
		}
		if (access(path, F_OK) == 0)
			return (free_all(local), path);
		free(path);
		i++;
	}
	free_all(local);
	return (NULL);
}

int	check_dir(char **path, char *cmd, t_exec *exec)
{
	struct stat	st;

	if (stat(*path, &st) != 0)
	{
		exec->exit_code = 127;
		perror(cmd);
		return (0);
	}
	if (S_ISDIR(st.st_mode))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 18);
		exec->exit_code = 126;
		return (0);
	}
	return (1);
}
