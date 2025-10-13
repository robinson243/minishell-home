/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 15:09:44 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/13 19:37:14 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	nb_type(t_node *node, int type)
// {
// 	t_node	*temp;
// 	int		i;

// 	i = 0;
// 	temp = node;
// 	while (temp != NULL)
// 	{
// 		if (temp->type == type)
// 			i++;
// 		temp = temp->next;
// 	}
// 	return (i);
// }

// char	**remp_command(t_node *data)
// {
// 	char	**str;
// 	t_node	*temp;
// 	int		i;

// 	i = 0;
// 	temp = data;
// 	str = malloc(sizeof(char *) * (nb_type(data, WORD) + 1));
// 	if (!str)
// 		return (NULL);
// 	while (temp != NULL)
// 	{
// 		if (temp->content == WORD)
// 		{
// 			str[i] = ft_strdup(temp->content);
// 			if (!str[i])
// 				return (NULL);
// 			i++;
// 		}
// 		temp = temp->next;
// 	}
// 	str[i] = NULL;
// 	return (str);
// }

// t_file	**remp_skipfile(t_node *data, int nb_out, int nb_in)
// {
// 	t_file	**str;
// 	t_node	*temp;
// 	int		i;
// 	int		j;

// 	j = 0;
// 	i = 0;
// 	temp = data;
// 	str = malloc(sizeof(t_file *) * ((nb_out + 1) + (nb_in + 1) + 1));
// 	if (!str)
// 		return (NULL);
// 	while (temp != NULL)
// 	{
// 		if (temp->type == OUTFILE && i < nb_out - 1)
// 		{
// 			str[i + j]->path = ft_strdup(temp->content);
// 			if (!str[i + j]->path)
// 				return (NULL);
// 			i++;
// 		}
// 		if (temp->type == INFILE && j < nb_in - 1)
// 		{
// 			str[i + j]->path = ft_strdup(temp->content);
// 			if (!str[i + j]->path)
// 				return (NULL);
// 			j++;
// 		}
// 		temp = temp->next;
// 	}
// 	str[i] = NULL;
// 	return (str);
// }

// void	do_struct(t_node *data)
// {
// 	t_cmd	*commande;

// 	commande->skipfile = NULL;
// 	commande->nb_infile = nb_type(data, INFILE);
// 	commande->nb_outfile = nb_type(data, OUTFILE);
// 	commande->command = remp_command(data);
// 	if (commande->nb_outfile >= 2 || commande->nb_infile >= 2)
// 		commande->skipfile = remp_skipfile(data, commande->nb_infile, commande->nb_outfile);
// 	if (commande->nb_infile)
// 		commande->inf = get_file(data, INFILE, commande->nb_infile);
// 	else
// 		commande->inf = NULL;
// 	if (commande->nb_outfile)
// 		commande->out = get_file(data, OUTFILE, commande->nb_outfile);
// 	else
// 		commande->out = NULL;
// }


