/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 16:10:43 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/20 15:45:38 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int		ft_pwd(void);

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
		if (ft_strncmp("HOME=", env[i], 5) == 0)
		{
			path_user = ft_strdup(env[i] + 5);
			if (!path_user)
				return (perror("Malloc"), NULL);
		}
		i++;
	}
	return (path_user);
}

void	maj_env(char *old_pwd, char *new_pwd, char ***env)
{
	int		pos;
	char	**tmp;
	char	*val;

	pos = existe("OLDPWD=", *env);
	if (pos != -1)
	{
		val = ft_strjoin_free(ft_strdup("OLDPWD="), old_pwd);
		tmp = export_update(pos, *env, val);
		free(val);
		if (!tmp)
			return ;
		*env = tmp;
	}
	pos = existe("PWD=", *env);
	if (pos != -1)
	{
		val = ft_strjoin_free(ft_strdup("PWD="), new_pwd);
		tmp = export_update(pos, *env, val);
		free(val);
		if (!tmp)
			return ;
		*env = tmp;
	}
}

int	ft_cd(char **cmd, char ***env)
{
	char	*path_user;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	path_user = NULL;
	if (cmd[1] && cmd[2])
		return (write(2, "cd: too many arguments\n", 24), free(old_pwd), 1);
	if (!cmd[1])
	{
		path_user = ft_user(*env);
		if (!path_user)
			return (1);
		if (chdir(path_user) != 0)
			return (perror("cd"), free(path_user), 1);
		return (free(path_user), maj_env(old_pwd, getcwd(NULL, 0), env), 0);
	}
	if (cmd[1][0] == '-' && !cmd[1][1])
		ft_pwd();
	else if (chdir(cmd[1]) != 0)
	{
		write(2, "cd: ", 4);
		write(2, cmd[1], ft_strlen(cmd[1]));
		write(2, ": No such file or directory\n", 29);
		return (free(old_pwd), 1);
	}
	return (maj_env(old_pwd, getcwd(NULL, 0), env), 0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char		*line;
// 	char		**res;

// 	(void)ac;
// 	(void)av;
// 	while (1)
// 	{
// 		line = readline("minishell> ");
// 		if (!line || line[0] == '9')
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		res = ft_split(line, ' ');
// 		if (ft_strncmp("cd", res[0], 2) == 0)
// 			ft_cd(res, env);
// 		if (ft_strncmp("pwd", res[0], 3) == 0)
// 			ft_pwd();
// 		free(line);
// 	}
// 	return (0);
// }
