/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:13:06 by romukena          #+#    #+#             */
/*   Updated: 2025/11/03 13:41:36 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

char	*mini_double_quoted(char *input, int *i, int *quoted)
{
	char	*tmp;

	tmp = extract_quoted(input, i);
	*quoted = 1;
	return (tmp);
}

char	*mini_single_quoted(char *input, int *i, int *quoted)
{
	char	*tmp;

	tmp = extract_single_quoted(input, i);
	*quoted = 2;
	return (tmp);
}

void	gain_some_lines(t_cmd **cur_cmd, t_cmd **head_cmd)
{
	if (!*cur_cmd)
	{
		*cur_cmd = new_cmd();
		if (!*head_cmd)
			*head_cmd = *cur_cmd;
	}
}

void	handle_pipe(t_cmd **cur_cmd, t_node *tmp)
{
	if (tmp->type == PIPE && tmp->next)
	{
		(*cur_cmd)->pipe_out = 1;
		(*cur_cmd)->next = new_cmd();
		*cur_cmd = (*cur_cmd)->next;
	}
}
