/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:47:28 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/19 15:17:15 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

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

int	len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	**unset(int i, char **env)
{
	char	**new_env;
	int		j;

	j = 0;
	new_env = malloc (sizeof(char *) * (len(env)));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (j != i)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (free_all(new_env), NULL);
			i++;
			j++;
		}
		else
			i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**ft_unset(char **cmd, char	**env)
{
	int		i;
	char	**new_env;

	i = 1;
	new_env = NULL;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		if (existe(cmd[i], env) != -1)
		{
			free_all(new_env);
			new_env = unset(existe(cmd[i], env), env);
			if (!new_env)
			{
				perror("malloc :");
				return (env);
			}
		}
		i++;
	}
	if (new_env == NULL)
		return (env);
	// free_all(env); // dupliquer le env sinon segfault
	return (new_env);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	**n;
// 	int		i;
// 	char	**env = envp;
// 	n = ft_unset(av + 1, env);
// 	while (n[i])
// 	{
// 		printf("%s\n", n[i]);
// 		i++;
// 	}
// 	// printf("%d", )
// }
