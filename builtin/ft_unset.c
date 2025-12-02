/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:47:28 by ydembele          #+#    #+#             */
/*   Updated: 2025/12/01 18:47:12 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

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
	int		l;

	l = 0;
	j = 0;
	new_env = malloc(sizeof(char *) * (len(env) + 1));
	if (!new_env)
		return (NULL);
	while (env[l])
	{
		if (l != i)
		{
			new_env[j] = ft_strdup(env[l]);
			if (!new_env[j])
				return (free_all(new_env), NULL);
			l++;
			j++;
		}
		else
			l++;
	}
	new_env[j] = NULL;
	return (new_env);
}

char	**ft_unset(char **cmd, char **env, t_exec *exec)
{
	int		i;
	int		idx;
	char	**new_env;
	char	**tmp;

	i = 1;
	new_env = env;
	while (cmd[i])
	{
		idx = existe(cmd[i], new_env);
		if (idx != -1)
		{
			tmp = unset(idx, new_env);
			if (!tmp)
			{
				exec->exit_code = 1;
				perror("malloc");
				return (new_env);
			}
			free_all(new_env);
			new_env = tmp;
		}
		i++;
	}
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
