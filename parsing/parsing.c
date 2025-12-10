/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:42:01 by romukena          #+#    #+#             */
/*   Updated: 2025/12/10 15:24:45 by romukena         ###   ########.fr       */
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
			if (r->file)
				free(r->file);
			r_tmp = r;
			r = r->next;
			free(r_tmp);
		}
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

int	check_pipe_syntax(t_node *tmp)
{
	if (!tmp)
		return (1);
	if (tmp->type == PIPE)
		return (0);
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			if (!tmp->next)
				return (0);
			if (tmp->next->type == PIPE)
				return (0);
		}
		if (tmp->quoted == 0 && (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
				|| tmp->type == REDIR_APPEND || tmp->type == HEREDOC)
			&& (!tmp->next || tmp->next->type != WORD))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}
static void process_token(t_cmd **cur_cmd, t_cmd **head_cmd, t_node **tmp, int *prv_code)
{
    t_redir *redir;

    if ((*tmp)->type != PIPE)
    {
        gain_some_lines(cur_cmd, head_cmd);
        if ((*tmp)->type == WORD)
            add_arg(*cur_cmd, (*tmp)->content);
        else if ((*tmp)->next && (*tmp)->next->type == WORD)
        {
            redir = new_redir((*tmp)->type, (*tmp)->next->content);
            if (!redir)
            {
                free_cmd_list_no_files(*head_cmd);
                c_p_code(prv_code);
                *head_cmd = NULL;
                return ;
            }
            add_redir(*cur_cmd, redir);
            *tmp = (*tmp)->next;
        }
    }
    if ((*tmp)->type == PIPE)
        handle_pipe(cur_cmd, *tmp);
}

t_cmd   *parser(t_node **head, int *prv_code)
{
    t_cmd   *head_cmd;
    t_cmd   *cur_cmd;
    t_node  *tmp;

    if (!check_pipe_syntax(*head))
        return (c_p_code(prv_code), ft_putstr_fd("Operator error\n", 2), NULL);
    init_var(&head_cmd, &cur_cmd, &tmp, head);
    while (tmp)
    {
        process_token(&cur_cmd, &head_cmd, &tmp, prv_code);
        if (!head_cmd)
            return (NULL);
        tmp = tmp->next;
    }
    return (head_cmd);
}
