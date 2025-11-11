/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:35:01 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/11 12:48:19 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

void	free_cmd_list(t_cmd *head)
{
	t_cmd	*cur;
	t_cmd	*tmp;
	t_redir	*r;
	t_redir	*r_tmp;

	cur = head;
	while (cur)
	{
		free_all(cur->argv);
		r = cur->redir;
		while (r)
		{
			r_tmp = r->next;
			if (r->file)
				free(r->file);
			free(r);
			r = r_tmp;
		}
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void	lst_clear(t_redir **lst)
{
	t_redir	*current;
	t_redir	*data_next;

	current = *lst;
	if (!*lst)
		return ;
	while (current)
	{
		data_next = current->next;
		free(current->file);
		free(current);
		current = data_next;
	}
	*lst = NULL;
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

void	free_exit(t_globale *data, char *msg, int code)
{
	t_exec	*exec;
	t_exec	*tmp;

	if (msg)
		perror(msg);
	if (!data)
		exit(code);
	exec = data->exec;
	clear_nodes(&data->node);
	if (data->exec && data->exec->cmd)
		free_cmd_list(data->exec->cmd);
	while (exec)
	{
		tmp = exec->next;
		my_close(exec->prev_nb, exec->infile, exec->p_nb[0], exec->p_nb[1]);
		my_close(exec->outfile, -1, -1, -1);
		free(exec);
		exec = tmp;
	}
	if (data->env)
		free_all(data->env);
	free(data);
	clear_history();
	exit(code);
}

void	free_exec(t_globale *data)
{
	t_exec	*exec;
	t_exec	*tmp;

	exec = data->exec;
	while (exec)
	{
		tmp = exec->next;
		my_close(exec->prev_nb, exec->infile, exec->p_nb[0], exec->p_nb[1]);
		my_close(exec->outfile, -1, -1, -1);
		free(exec);
		exec = tmp;
	}
	free(data);
}

int		is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_globale *data, t_cmd *cmd, t_exec *exec)
{
	int			err;
	long long	res;

	err = 0;
	if (cmd->argv[1] && cmd->argv[2])
	{
		write(2, "exit: too many arguments\n", 26);
		exec->exit_code = 1;
		return ;
	}
	if (cmd->argv[1])
	{
		res = my_atoi(cmd->argv[1], &err);
		if (err || !is_num(cmd->argv[1]))
		{
			write(2, "exit: ", 7);
			write(2, cmd->argv[1], ft_strlen(cmd->argv[1]));
			write(2, ": numeric argument required\n", 29);
			free_exit(data, NULL, 2);
		}
	}
	if (!cmd->argv[1])
		free_exit(data, NULL, 0);
	free_exit(data, NULL, (int)(res % 256));
}
