/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 18:11:39 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/30 15:06:51 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		return (1);
	return (0);
}

int	pars(char *line)
{
	if (line[0] == '|' || line[ft_len(line) - 1] == '|'
		|| line[ft_len(line) - 1] == '>' || line[ft_len(line) - 1] == '<')
		return (1);
	return (0);
}

int	all_parsing(t_node **data, char *line)
{
	if (quote(line))
		return (1);
	if (pars(line))
		return (1);
	args_content(data, line);
	return (0);
}