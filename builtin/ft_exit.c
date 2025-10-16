/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:35:01 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/16 19:16:47 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exit(t_cmd *cmd, int code)
{
	free_all(cmd->command);
	while (cmd->list)
	{
		free(cmd->list->path);
		cmd->list = cmd->list->next;
	}
	my_close(cmd->infile, cmd->outfile, cmd->p_nb[0], cmd->p_nb[1]);
	my_close(cmd->prev_nb, -1, -1, -1);
	exit(code);
}

void	ft_exit(t_globale *data, t_cmd *cmd)
{
	int	err;

	if (!cmd->command[1])
		free_exit(cmd, 0);
}
