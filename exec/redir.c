/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:13:08 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/16 02:54:47 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	open_file(t_exec *exec)
{
	t_redir	*tmp;

	while (exec)
	{
		tmp = exec->cmd->redir;
		if (!tmp)
		{
			exec = exec->next;
			continue ;
		}
		while (tmp)
		{
			if (tmp->type == REDIR_IN || tmp->type == HEREDOC)
				my_close(exec->infile, -1, -1, -1);
			else
				my_close(exec->outfile, -1, -1, -1);
			if (!my_open(tmp, exec))
			{
				exec->skip_cmd = true;
				break ;
			}
			tmp = tmp->next;
		}
		exec = exec->next;
	}
}

void	redir_in(t_exec *exec)
{
	if (exec->first == 0 && exec->infile == -1)
	{
		if (dup2(exec->prev_nb, 0) == -1)
			exec->skip_cmd = true;
	}
	else if (exec->infile != -1)
	{
		if (dup2(exec->infile, 0) == -1)
			exec->skip_cmd = true;
	}
	if (exec->infile != -1)
		close(exec->infile);
	if (exec->prev_nb >= 0)
		close(exec->prev_nb);
	close(exec->p_nb[0]);
}

void	redir_out(t_exec *exec)
{
	if (exec->next != NULL && exec->outfile == -1)
	{
		if (dup2(exec->p_nb[1], 1) == -1)
			exec->skip_cmd = true;
	}
	else if (exec->outfile != -1)
	{
		if (dup2(exec->outfile, 1) == -1)
			exec->skip_cmd = true;
		close(exec->outfile);
	}
	my_close(exec->p_nb[1], -1, -1, -1);
}

void	redir_in_out(t_exec *exec)
{
	redir_in(exec);
	redir_out(exec);
}

int	my_open(t_redir *list, t_exec *exec)
{
	t_cmd	*cmd;

	(void)cmd;
	cmd = exec->cmd;
	if (!list || !list->file)
		return (1);
	if (list->type == REDIR_IN)
		exec->infile = open(list->file, O_RDONLY);
	else if (list->type == REDIR_OUT)
		exec->outfile = open(list->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (list->type == REDIR_APPEND)
		exec->outfile = open(list->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (list->type == HEREDOC)
		exec->infile = my_here_doc(list->file);
	if ((list->type == REDIR_IN) && exec->infile == -1)
		return (perror(list->file), 0);
	else if ((list->type == REDIR_OUT || list->type == REDIR_APPEND)
		&& exec->outfile == -1)
		return (perror(list->file), 0);
	else if (list->type == HEREDOC && exec->infile == -1)
		return (0);
	return (1);
}
