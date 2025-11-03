/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 12:42:01 by romukena          #+#    #+#             */
/*   Updated: 2025/11/03 13:03:09 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_cmd *parser(t_node **head)
{
	t_cmd *head_cmd;
	t_cmd *cur_cmd;
	t_node	*tmp;

	tmp = *head;
	head_cmd = NULL;
	cur_cmd = NULL;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (!cur_cmd)
			{
				cur_cmd = new_cmd();
				if (!head_cmd)
					head_cmd = cur_cmd;
			}	
			add_arg(cur_cmd, tmp->content);
		}
		else if (tmp->type != PIPE && tmp->type != WORD)
		{
			if (!cur_cmd)
			{
				cur_cmd = new_cmd();
				if (!head_cmd)
					head_cmd = cur_cmd;
			}	
			add_redir(cur_cmd, new_redir(tmp->type, tmp->content));
		}
		if (tmp->type == PIPE && tmp->next)
		{
			cur_cmd->pipe_out = 1;
			cur_cmd->next = new_cmd();
			cur_cmd = cur_cmd->next;
		}
		tmp = tmp->next;
	}
	return (head_cmd);
}

void free_cmd_list_no_files(t_cmd *head)
{
    t_cmd *cur;
    t_cmd *tmp;

	cur = head;
    while (cur)
    {
        if (cur->argv)
        {
            for (int i = 0; cur->argv[i]; i++)
                free(cur->argv[i]);
            free(cur->argv);
        }
        t_redir *r = cur->redir;
        t_redir *r_tmp;
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

