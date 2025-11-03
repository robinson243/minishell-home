/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:41:37 by romukena          #+#    #+#             */
/*   Updated: 2025/11/03 12:37:11 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_cmd	*new_cmd(void)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (NULL);
	node->argv = NULL;
	node->pipe_out = 0;
	node->redir = NULL;
	node->next = NULL;
	return (node);
}

t_redir	*new_redir(int type, char *file)
{
	t_redir	*node;

	node = malloc(sizeof(t_redir));
	if (!node)
		return (NULL);
	node->file = file;
	node->type = type;
	node->next = NULL;
	return (node);
}

void	add_redir(t_cmd *cmd, t_redir *new)
{
	t_redir	*tmp;

	tmp = cmd->redir;
	if (!cmd->redir)
	{
		cmd->redir = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	len_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		i;
	int		j;
	int		len;
	char	**tab;

	i = 0;
	j = 0;
	len = len_tab(cmd->argv);
	tab = malloc(sizeof(char *) * (len + 2));
	while (cmd->argv && cmd->argv[i])
	{
		tab[i] = ft_strdup(cmd->argv[i]);
		i++;
	}
	tab[i] = ft_strdup(arg);
	tab[i + 1] = NULL;
	while (cmd->argv && cmd->argv[j])
		free(cmd->argv[j++]);
	free(cmd->argv);
	cmd->argv = tab;
}
