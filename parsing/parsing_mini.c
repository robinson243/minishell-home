/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_mini.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 14:25:45 by romukena          #+#    #+#             */
/*   Updated: 2025/11/18 14:26:27 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	process_word_node(t_cmd *cur_cmd, t_node *tmp, t_node **last_word_node)
{
	if (tmp->type == WORD)
	{
		add_arg(cur_cmd, tmp->content);
		*last_word_node = tmp;
	}
	else if (tmp->next && tmp->next->type == WORD)
	{
		add_redir(cur_cmd, new_redir(tmp->type, tmp->next->content));
	}
}

void	process_pipe_node(t_cmd **cur_cmd, t_node *tmp, t_node **last_word_node)
{
	if (*last_word_node)
		(*cur_cmd)->quoted = (*last_word_node)->quoted;
	handle_pipe(cur_cmd, tmp);
	*last_word_node = NULL;
}
