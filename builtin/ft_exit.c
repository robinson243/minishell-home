/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:35:01 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/03 16:11:43 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

void	lst_clear(t_file **lst)
{
	t_file	*current;
	t_file	*data_next;

	current = *lst;
	if (!*lst)
		return ;
	while (current)
	{
		data_next = current->next;
		free(current->path);
		free(current);
		current = data_next;
	}
	*lst = NULL;
}

void	cmd_clear(t_cmd **lst)
{
	t_cmd	*current;
	t_cmd	*data_next;

	current = *lst;
	if (!*lst)
		return ;
	while (current)
	{
		data_next = current->next;
		free_all(current->command);
		my_close(current->infile, current->outfile, current->p_nb[0], current->p_nb[1]);
		my_close(current->prev_nb, -1, -1, -1);
		lst_clear(&current->list);
		free(current);
		current = data_next;
	}
	*lst = NULL;
}

void	free_exit(t_globale *data, char *str, int code)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	if (str)
		perror(str);
	cmd_clear(&data->cmd);
	free_all(data->env);
	free(data);
	exit(code);
}

long long	my_atoi(char *s, int *err)
{
	int			i;
	int			signe;
	long long	result;

	signe = 1;
	i = 0;
	result = 0;
	while (s[i] == ' ')
		i++;
	if (s[i] == '-')
	{
		signe = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		result = result * 10 + s[i] - 48;
		i++;
	}
	result = result * signe;
	if (result > INT_MAX || result < INT_MIN)
		*err = 1;
	return (result);
}

void	ft_exit(t_globale *data, t_cmd *cmd)
{
	int			err;
	long long	res;

	err = 0;
	if (cmd->command[1])
	{
		res = my_atoi(cmd->command[1], &err);
		if (err)
		{
			write(2, "exit: ", 7);
			write(2, cmd->command[1], ft_strlen(cmd->command[1]));
			write(2, ": numeric argument required\n", 29);
			free_exit(data, NULL, 2);
		}
	}
	if (cmd->command[1] && cmd->command[2])
	{
		write(2, "exit: too many arguments\n", 26);
		cmd->exit_code = 1;
		return ;
	}
	if (!cmd->command[1])
		free_exit(data, NULL, 0);
	free_exit(data, NULL, (int)(res % 256));
}
