/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:41:37 by romukena          #+#    #+#             */
/*   Updated: 2025/11/01 10:26:00 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	numb_of_commands(t_node **head)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = *head;
	if (!head || !(*head))
		return (i) ;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (i);
		tmp = tmp->next;
		i++;
	}
	return (i);
}
