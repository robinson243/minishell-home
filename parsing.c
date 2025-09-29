/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:11:39 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/29 18:46:56 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	quote(char *line)
{
	int	doubl;
	int	single;
	int	i;

	i = 0;
	doubl = 0;
	single = 0;
	while (line[i])
	{
		if (doubl == 0 && single == 0 && line[i] == '"')
			doubl = 1;
		else if (doubl == 1 && single == 0 && line[i] == '"')
			doubl = 0;
		else if (doubl == 0 && single == 0 && line[i] == '\'')
			single = 1;
		else if (doubl == 0 && single == 1 && line[i] == '\'')
			single = 0;
		i++;
	}
	if (doubl != 0 || single != 0)
	{
		printf("minishell: syntax error: unclosed quote\n");
		return (1);
	}
	return (0);
}

int	pars(char *line)
{
	if (line[0] == '|' || line[ft_len(line) - 1] == '|'
		|| line[ft_len(line) - 1] == '>' || line[ft_len(line) - 1] == '<')
	{
		printf("minishell: syntaxe error near unexpected token: `|'\n");
		return (1);
	}
	return (0);
}

int	pars_deux(t_node *data)
{
	t_node	*tmp;
	int		type;

	tmp = data;
	while (tmp != NULL)
	{
		type = tmp->type;
		if (type >= REDIR_IN && type <= REDIR_APPEND)
		{
			if (tmp->next->type != WORD)
			{
				printf("%s `%s'\n", ERROR_SYNTAX, tmp->next->content);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	nb_type(t_node *node, int type, int stop)
{
	t_node	*temp;
	int		i;

	i = 0;
	temp = node;
	while (temp != NULL && temp->type != stop)
	{
		if (temp->type == type)
			i++;
		temp = temp->next;
	}
	return (i);
}

void	pars_file(t_globale **data)
{
	t_node	*head;

	head = (*data)->node;
	while ((*data)->node != NULL)
	{
		if ((*data)->node->type == REDIR_IN)
			(*data)->node->next->type = INFILE;
		else if ((*data)->node->type == REDIR_OUT
			|| (*data)->node->type == REDIR_APPEND)
			(*data)->node->next->type = OUTFILE;
		(*data)->node = (*data)->node->next;
	}
	(*data)->node = head;
}

int	parse_commande(t_globale *data)
{
	int		i;
	int		n_cmd;
	int		n_inf;
	int		n_out;
	int		j;

	pars_file(data);
	j = nb_type(data->node, PIPE, -1);
	i = 0;
	data->cmd = NULL;
	while (i < j)
	{
		ft_add_cmd(data->cmd, ft_lstnew_cmd(nb_type(data->node, WORD, PIPE),nb_type(data->node, INFILE, PIPE), nb_type(data->node, OUTFILE, PIPE)));
		
	}
}

int	all_parsing(t_globale **data, char *line)
{
	(*data)->node = NULL;
	if (quote(line))
		return (1);
	if (pars(line))
		return (1);
	args_content(&(*data)->node, line);
	if (pars_deux((*data)->node))
		return (1);
	pars_file(data);
	return (0);
}
