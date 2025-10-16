/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:13:08 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/16 20:11:33 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_in(t_cmd *cmd)
{
	if (cmd->first == 0 && cmd->infile == -1)
	{
		if (dup2(cmd->prev_nb, 0) == -1)
			cmd->skip_cmd = true;
	}
	else if (cmd->infile != -1)
	{
		if (dup2(cmd->infile, 0) == -1)
			cmd->skip_cmd = true;
	}
	if (cmd->infile != -1)
		close(cmd->infile);
}

void	redir_out(t_cmd *cmd)
{
	if (cmd->next != NULL && cmd->outfile == -1)
	{
		if (dup2(cmd->p_nb[1], 1) == -1)
			cmd->skip_cmd = true;
	}
	else if (cmd->outfile != -1)
	{
		if (dup2(cmd->outfile, 1) == -1)
			cmd->skip_cmd = true;
	}
	if (cmd->outfile != -1)
		close(cmd->outfile);
}

void	redir_in_out(t_cmd *cmd)
{
	redir_in(cmd);
	if (cmd->skip_cmd == true)
		return ;
	redir_out(cmd);
}

int	my_open(t_file *list, t_cmd *cmd)
{
	if (!list || !list->path)
		return (-1);
	if (list->type == INFILE)
		cmd->infile = open(list->path, O_RDONLY);
	else if (list->type == OUTFILE)
		cmd->outfile = open(list->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (list->type == OUT_APPEND)
		cmd->outfile = open(list->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (list->type == HEREDOC)
		cmd->infile = heredoc();
	else
		list->fd = -1;
	if ((list->type == INFILE || list->type == HEREDOC) && cmd->infile == -1)
	{
		perror(list->path);
		return (0);
	}
	else if ((list->type == OUTFILE || list->type == OUT_APPEND)
		&& cmd->outfile == -1)
	{
		perror(list->path);
		return (0);
	}
	return (1);
}
