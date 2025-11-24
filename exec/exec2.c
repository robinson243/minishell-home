/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dems <dems@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 15:53:29 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/23 19:38:08 by dems             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int exist(char **path, t_cmd *command, t_globale *data, t_exec *exec)
{
    *path = NULL;

	if (!command->argv[0][0] || (command->argv[0][0] == '.'
		&& (!command->argv[0][1] || (command->argv[0][1] == '.' 
			&& !command->argv[0][2]))))
	{
		exec->exit_code = 127;
		return (0);
	}
    if (ft_strchr(command->argv[0], '/'))
        *path = ft_strdup(command->argv[0]);
    else
        *path = get_path(data->env, command->argv[0], data->exec);
    if (!*path)
    {
        ft_putstr_fd(command->argv[0], 2);
        ft_putstr_fd(": command not found\n", 2);
        exec->exit_code = 127;
        return (0);
    }
    if (!check_dir(path, command->argv[0], exec))
        return (0);
    if (access(*path, X_OK) != 0)
    {
        exec->exit_code = 127;
        perror(*path);
        return (free(*path), 0);
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
	if (!local && exec->exit_code == 1)
		return (NULL);
	else if (!local && exec->exit_code == 0)
		return (cmd);
	while (local[i])
	{
		path = ft_strslashjoin(local[i], cmd);
		if (!path)
		{
			exec->exit_code = 1;
			free_all(local);
			return (NULL);
		}
		if (access(path, F_OK) == 0)
			return (free_all(local), path);
		free(path);
		i++;
	}
	free_all(local);
	return (NULL);
}

// char *get_path(char **env, char *cmd, t_exec *exec)
// {
//     char **local;
//     char *path;
//     int i;

//     if (ft_strchr(cmd, '/')) // chemin absolu ou relatif
//     {
//         if (access(cmd, F_OK) != 0)
//             return NULL;
//         return ft_strdup(cmd);
//     }

//     local = remp_local(env, exec);
//     if (!local)
//         return NULL;

//     i = 0;
//     while (local[i])
//     {
//         path = ft_strslashjoin(local[i], cmd);
//         if (!path)
//         {
//             exec->exit_code = 1;
//             free_all(local);
//             return NULL;
//         }
//         if (access(path, F_OK) == 0)
//             return (free_all(local), path);
//         free(path);
//         i++;
//     }
//     free_all(local);
//     return NULL;
// }

int	check_dir(char **path, char *cmd, t_exec *exec)
{
	struct stat	st;

	if (stat(*path, &st) != 0)
		return (1);
	if (S_ISDIR(st.st_mode))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Is a directory\n", 18);
		free(*path);
		exec->exit_code = 126;
		return (0);
	}
	return (1);
}
