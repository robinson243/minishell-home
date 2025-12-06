/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:01:01 by ydembele          #+#    #+#             */
/*   Updated: 2025/12/06 18:11:03 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	init(t_exec *new)
{
	new->skip_cmd = false;
	new->exit_code = 0;
	new->prev_nb = -1;
	new->infile = -1;
	new->outfile = -1;
	new->p_nb[0] = -1;
	new->p_nb[1] = -1;
	new->next = NULL;
}

t_exec	*init_exec(t_cmd *cmd, t_globale *data)
{
	t_exec		*head;
	t_exec		*curr;
	t_exec		*new;
	t_cmd		*tmp;

	data->exec = NULL;
	head = NULL;
	curr = NULL;
	tmp = cmd;
	while (tmp)
	{
		new = malloc(sizeof(t_exec));
		if (!new)
			return (free_exec(data), NULL);
		new->cmd = tmp;
		new->first = (tmp == cmd);
		init(new);
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		tmp = tmp->next;
	}
	return (head);
}

void	init_data(t_globale *data, t_node *node, int prv_code)
{
	data->node = node;
	data->preview_code = prv_code;
}
