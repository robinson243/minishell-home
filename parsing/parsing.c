/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:42:01 by romukena          #+#    #+#             */
/*   Updated: 2025/11/18 14:26:33 by romukena         ###   ########.fr       */
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

int	check_pipe_syntax(t_node *tmp)
{
	if (!tmp)
		return (1);
	if (tmp->type == PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE && (!tmp->next || tmp->next->type == PIPE))
			return (0);
		if (tmp->type != WORD && (!tmp->next || tmp->next->type != WORD))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

t_cmd	*parser(t_node **head)
{
	t_cmd	*head_cmd;
	t_cmd	*cur_cmd;
	t_node	*tmp;
	t_node	*last_word_node;

	if (!check_pipe_syntax(*head))
		return (ft_putstr_fd("Operator error\n", 2), NULL);
	init_var(&head_cmd, &cur_cmd, &tmp, head);
	last_word_node = NULL;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type != PIPE)
		{
			gain_some_lines(&cur_cmd, &head_cmd);
			process_word_node(cur_cmd, tmp, &last_word_node);
		}
		if (tmp->type == PIPE)
			process_pipe_node(&cur_cmd, tmp, &last_word_node);
		tmp = tmp->next;
	}
	if (last_word_node)
		cur_cmd->quoted = last_word_node->quoted;
	return (head_cmd);
}
