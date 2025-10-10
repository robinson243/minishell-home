/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/10 14:24:03 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* int	main(int ac, char **av)
{
	char	*line;
	char	*mysentence;
	char	**split_cmd;
	char	*str;
	int		val;
	char	*str;
	char	*str;
	t_cmd	*tmp;

	(void)ac;
	(void)av;
	using_history();
	while ((line = readline("minishell > ")) != NULL)
	{
		mysentence = ft_strdup(line);
		if (!mysentence)
			return (free(line), (0));
		split_cmd = ft_split(mysentence, ' ');
		if (!split_cmd)
			free_all(split_cmd);
		for (int i = 0; split_cmd[i]; i++)
		{
			printf("word %s\n", split_cmd[i]);
		}
		add_history(line);
		free(line);
	}
	clear_history();
	return (0);
} */


t_node	*create_node(char *content)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

void	add_node(t_node **head, t_node *new)
{
	t_node	*current;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

void	free_node(t_node **head)
{
	
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}


int	single_double_quotes(char *str)
{
	int	i;
	int single_quote;
	int double_quotes;
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			double_quotes++;
		if (str[i] == '\'')
			single_quote++;
		i++;
	}
	if ((single_quote + double_quotes) % 2 == 0 )
		return (1);
	return (-1);
}

int	main(void)
{

	int		i;
	int		j;
	int		k;
	char	*str;
	char *tmp;
	t_node	*head = NULL;
	
	i = 0;
	j = 0;
	k = 0;
	str = "echo \"salut les gens\" ";
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			i++;
		j = i;
		while (str[i] && !ft_isspace(str[i]))
			i++;
		if (j >= i)
			continue ;
		head->content = ft_substr(i, j, j - i);
			
		
		
		
		i++;
	}
	return (0);
}
