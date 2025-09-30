/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:27:21 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/30 18:02:19 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arg_type(char *str)
{
	if (verif(str[0], ">|<"))
		return (0);
	if (str[0] && str[1] && str[0] == '>' && str[1] == '>')
		return (4);
	if (str[0] && str[1] && str[0] == '<' && str[1] == '<')
		return (5);
	if (verif(str[0], ">") == 0)
		return (3);
	if (verif(str[0], "<") == 0)
		return (2);
	if (verif(str[0], "|") == 0)
		return (1);
	return (-1);
}

int	args_content(t_node **data, char *line)
{
	int		i;
	char	*str;

	str = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				str = append_char(str, line[i++]);
		}
		else if (verif(line[i], ">|< "))
		{
			while (line[i] != 0 && verif(line[i], ">|< ") == 1)
				str = append_char(str, line[i++]);
		}
		else if ((line[i] == '>' && line[i + 1] == '>')
			|| (line[i] == '<' && line[i + 1] == '<'))
		{
			str = append_char(str, line[i++]);
			str = append_char(str, line[i++]);
		}
		else if (verif(line[i], ">|<") == 0)
			str = append_char(str, line[i++]);
		if (line[i] == ' ')
			i++;
		if (!ft_lstaddback(data, ftlstnew(str, arg_type(str))))
			return (ftlstclear(data), 0);
		free(str);
		str = NULL;
	}
	return (0);
}

int	main(int ac, char **av)
{
	char	*line;
	t_node	*data;

	data = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("minishell> ");
		if (!line || line[0] == '9')
		{
			printf("exit\n");
			break ;
		}
		if (*line)
			add_history(line);
		printf("Vous avez tapÃ© : %s\n", line);
		all_parsing(&data, line);
		free(line);
	}
	print_list(data);
	ftlstclear(&data);
	return (0);
}
