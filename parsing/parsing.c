/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:42:01 by romukena          #+#    #+#             */
/*   Updated: 2025/11/04 14:58:31 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

void	free_cmd_list_no_files(t_cmd *head)
{
	t_cmd	*cur;
	t_cmd	*tmp;
	t_redir	*r;
	t_redir	*r_tmp;

	cur = head;
	while (cur)
	{
		free_argv(cur->argv);
		r = cur->redir;
		while (r)
		{
			r_tmp = r;
			r = r->next;
			free(r_tmp);
		}
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void	init_var(t_cmd **head_cmd, t_cmd **cur_cmd, t_node **tmp, t_node **head)
{
	*head_cmd = NULL;
	*cur_cmd = NULL;
	*tmp = *head;
}

t_cmd	*parser(t_node **head)
{
	t_cmd	*head_cmd;
	t_cmd	*cur_cmd;
	t_node	*tmp;

	init_var(&head_cmd, &cur_cmd, &tmp, head);
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type != PIPE)
		{
			gain_some_lines(&cur_cmd, &head_cmd);
			if (tmp->type == WORD)
				add_arg(cur_cmd, tmp->content);
			else if (tmp->next && tmp->next->type == WORD)
			{
				add_redir(cur_cmd, new_redir(tmp->type, tmp->next->content));
				tmp = tmp->next;
			}
		}
		if (tmp->type == PIPE)
			handle_pipe(&cur_cmd, tmp);
		tmp = tmp->next;
	}
	return (head_cmd);
}
