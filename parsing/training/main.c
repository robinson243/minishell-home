/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/13 03:30:52 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

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

void	clear_nodes(t_node **head)
{
	t_node	*current;
	t_node	*tmp;

	if (*head == NULL)
		return ;
	current = *head;
	while (current)
	{
		tmp = current->next;
		free(current->content);
		free(current);
		current = tmp;
	}
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

void	print_list(t_node **head)
{
	t_node	*tmp;

	if (!head || !*head)
	{
		printf("(liste vide)\n");
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		printf("[%d] ", tmp->index);
		if (tmp->content)
			printf("%s\n", tmp->content);
		else
			printf("(null)\n");
		tmp = tmp->next;
	}
}

char	*extract_quoted(char *str, int *i)
{
	int		j;
	char	*res;

	j = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != '"')
	{
		(*i)++;
	}
	if (str[*i] == '\0')
		return (NULL);
	res = ft_substr(str, j, (*i - j));
	(*i)++;
	return (res);
}

char	*extract_word(char *str, int *i)
{
	int		j;
	char	*res;

	while (is_space(str[*i]))
		(*i)++;
	if (!is_space(str[*i]))
		j = *i;
	while (str[*i] && !is_space(str[*i]))
		(*i)++;
	res = ft_substr(str, j, (*i - j));
	return (res);
}

t_node	*lexer(char *input, t_node **head)
{
	int	i;
	char	*word;

	i = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (input[i] == '"')
			word = extract_quoted(input, &i);
		else
			word = extract_word(input, &i);
		add_node(head, create_node(word));
	}
	return (*head);
}

int	main(void)
{
	char	*str;
	t_node	*head;

	head = NULL;
	str = "echo \"bonjour le monde\" apres c'est quoi ";
	lexer(str, &head);
	print_list(&head);
	clear_nodes(&head);
	return (0);
}
