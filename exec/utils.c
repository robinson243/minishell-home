/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:26:31 by ydembele          #+#    #+#             */
/*   Updated: 2025/12/10 15:24:06 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	my_close(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 >= 0)
		close(fd1);
	if (fd2 >= 0)
		close(fd2);
	if (fd3 >= 0)
		close(fd3);
	if (fd4 >= 0)
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
	if (!ft_strncmp(command, "echo", INT_MAX))
		return (1);
	return (0);
}

void	do_builtin(t_globale *data, t_exec *exec)
{
	char	**commande;
	int		std;

	commande = exec->cmd->argv;
	if (exec->skip_cmd)
		exec->exit_code = 1;
	if (!ft_strncmp(commande[0], "exit", INT_MAX))
		ft_exit(data, exec->cmd, exec);
	commande = expand_star_argv(exec->cmd->argv);
	std = dup(1);
	redir_out(exec);
	if (!ft_strncmp(commande[0], "unset", INT_MAX))
		data->env = ft_unset(commande, data->env, exec);
	if (!ft_strncmp(commande[0], "pwd", INT_MAX))
		exec->exit_code = ft_pwd();
	if (!ft_strncmp(commande[0], "env", INT_MAX))
		exec->exit_code = env(data->env, commande);
	if (!ft_strncmp(commande[0], "export", INT_MAX))
		data->env = ft_export(commande, data->env, exec);
	if (!ft_strncmp(commande[0], "cd", INT_MAX))
		exec->exit_code = ft_cd(commande, data->env, data);
	if (!ft_strncmp(commande[0], "echo", INT_MAX))
		exec->exit_code = ft_echo(commande + 1);
	free_all(commande);
	(dup2(std, 1), close(std));
}

void	next(t_exec *exec)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (exec->next)
		tmp_fd = exec->p_nb[0];
	my_close(exec->prev_nb, exec->infile, exec->p_nb[1], exec->outfile);
	if (exec->next)
		exec->next->prev_nb = tmp_fd;
	else if (exec->p_nb[0] >= 0)
		close(exec->p_nb[0]);
}
