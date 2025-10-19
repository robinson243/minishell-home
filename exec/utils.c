/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:26:31 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/19 14:58:02 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_close(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 != 1)
		close(fd1);
	if (fd2 != 1)
		close(fd2);
	if (fd3 != 1)
		close(fd3);
	if (fd4 != 1)
		close(fd4);
}

char	*ft_strslashjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
	res[j++] = '/';
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = 0;
	return (res);
}

int	is_builtin(char	*command)
{
	if (!command)
		return (0);
	if (!ft_strncmp(command, "unset", INT_MAX))
		return (1);
	if (!ft_strncmp(command, "exit", INT_MAX))
		return (1);
	if (!ft_strncmp(command, "pwd", INT_MAX))
		return (1);
	if (!ft_strncmp(command, "env", INT_MAX))
		return (1);
	if (!ft_strncmp(command, "export", INT_MAX))
		return (1);
	if (!ft_strncmp(command, "cd", INT_MAX))
		return (1);
	return (0);
}

int	do_builtin(t_globale *data, t_cmd *cmd)
{
	char	**commande;

	commande = cmd->command;
	if (cmd->skip_cmd)
	{
		data->exit_code = 1;
		return (0);
	}
	if (!ft_strncmp(commande[0], "unset", INT_MAX))
		data->env = ft_unset(commande, data->env);
	if (!ft_strncmp(commande[0], "exit", INT_MAX))
		ft_exit(data, cmd);
	if (!ft_strncmp(commande[0], "pwd", INT_MAX))
		cmd->exit_code = ft_pwd();
	if (!ft_strncmp(commande[0], "env", INT_MAX))
		cmd->exit_code = env(data->env);
	// if (!ft_strncmp(commande[0], "export", INT_MAX))
	// 	ft_export();
	if (!ft_strncmp(commande[0], "cd", INT_MAX))
		cmd->exit_code = ft_cd(commande, data->env);
	if (!ft_strncmp(commande[0], "echo", INT_MAX))
		cmd->exit_code = ft_echo(commande + 1);
	return (0);
}
