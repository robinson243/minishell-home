/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/14 12:12:25 by romukena         ###   ########.fr       */
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
int	recognize_token(char *str, int *i)
{
	if (str[*i] == '|')
		return (PIPE);
	if (str[*i] == '<' && str[*i + 1] && str[*i + 1] != '<')
		return (REDIR_IN);
	if (str[*i] == '<' && str[*i + 1] && str[*i + 1] == '<')
		return (HEREDOC);
	if (str[*i] == '>' && str[*i + 1] && str[*i + 1] != '>')
		return (REDIR_OUT);
	if (str[*i] == '>' && str[*i + 1] && str[*i + 1] == '>')
		return (REDIR_APPEND);
	else
		return (WORD);
}

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

char	*extract_single_quoted(char *str, int *i)
{
	int		j;
	char	*res;

	j = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
	}
	if (str[*i] == '\0')
		return (NULL);
	res = ft_substr(str, j, (*i - j));
	(*i)++;
	return (res);
}


char	*extract_operator(char *str, int *i)
{
	int	j;
	char	*res;
	j = *i;
	if (recognize_token(str, i) != WORD)
	{
		if (recognize_token(str, i) == REDIR_APPEND || recognize_token(str, i) == HEREDOC)
		{
			res = ft_substr(str, j, 2);
			(*i)++;
		}
		else
			res = ft_substr(str, j, 1);
	}
	(*i)++;
	return (res);
}

char	*extract_word(char *str, int *i)
{
	int		j;
	char	*res;

	while (is_space(str[*i]))
		(*i)++;
	if (!str[*i])
		return (NULL);
	j = *i;
	if (recognize_token(str, i) != WORD)
		return (extract_operator(str, i));
	while (str[*i] && !is_space(str[*i]) && str[*i] != '"')
	{
		if (recognize_token(str, i) != WORD)	
			return (ft_substr(str, j, (*i - j)));
		(*i)++;
	}
	res = ft_substr(str, j, (*i - j));
	return (res);
}

t_node	*lexer(char *input, t_node **head)
{
	int		i;
	char	*word;

	i = 0;
	while (input[i])
	{
		while (is_space(input[i]))
			i++;
		if (input[i] == '"')
			word = extract_quoted(input, &i);
		else if (input[i] == '\'')
			word = extract_single_quoted(input, &i);
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
	str = "mot>>guillemets";
	lexer(str, &head);
	print_list(&head);
	clear_nodes(&head);
	return (0);
}
