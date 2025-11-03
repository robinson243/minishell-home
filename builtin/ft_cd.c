/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:10:43 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/30 17:56:14 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_user(char **env)
{
	int		i;
	char	*path_user;

	path_user = NULL;
	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp("ZDOTDIR=", env[i], 8) == 0)
		{
			path_user = ft_strdup(env[i] + 8);
			if (!path_user)
				return (NULL);
		}
		i++;
	}
	return (path_user);
}

int	ft_cd(char	**cmd, char **env)
{
	char	*path_user;

	if (!cmd[1])
	{
		path_user = ft_user(env);
		if (!path_user)
			return (1);
		if (chdir(path_user) != 0)
		{
			perror("cd");
			return (1);
		}
		return (0);
	}
	else
	{
		printf("%s\n", cmd[1]);
		if (chdir(cmd[1]) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}

int main(int ac, char **av, char **env)
{
	ft_cd(av + 1, env);
    return 0;
}
