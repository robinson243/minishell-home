/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/22 12:07:21 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	recognize_token(char *str, int *i)
{
	if (str[*i] == '|')
		return (PIPE);
	if (str[*i] == '<' && str[*i + 1] != '<')
		return (REDIR_IN);
	if (str[*i] == '<' && str[*i + 1] == '<')
		return (HEREDOC);
	if (str[*i] == '>' && str[*i + 1] != '>')
		return (REDIR_OUT);
	if (str[*i] == '>' && str[*i + 1] == '>')
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
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching '\"'\n",
			2);
		return (NULL);
	}
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
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching '\''\n",
			2);
		return (NULL);
	}
	res = ft_substr(str, j, (*i - j));
	(*i)++;
	return (res);
}

char	*extract_operator(char *str, int *i)
{
	int		j;
	char	*res;
	int		filter_operator;

	filter_operator = recognize_token(str, i);
	j = *i;
	if (filter_operator != WORD)
	{
		if (filter_operator == REDIR_APPEND || filter_operator == HEREDOC)
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

char	*extract_dollar(char *str, int *i)
{
	int		j;
	char	*res;

	(*i)++;
	j = *i;
	if (str[*i] == '?')
	{
		res = ft_strdup("?");
		(*i)++;
		return (res);
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	res = ft_substr(str, j, (*i - j));
	return (res);
}

char	*extract_word(char *str, int *i)
{
	int		j;
	char	*tmp;
	char	*res;
	char	*dollar_string;

	dollar_string = "";
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
	tmp = ft_substr(str, j, (*i - j));
	res = handle_quote_management(tmp, str, i);
	return (res);
}

char	*handle_quote_management(char *tmp, char *str, int *i)
{
	char	*quoted_word;
	char	*res;

	res = "";
	while (str[*i] && recognize_token(str, i) == WORD && !is_space(str[*i]))
	{
		if (str[*i] == '\'')
		{
			quoted_word = extract_single_quoted(str, i);
			res = ft_strjoin(res, quoted_word);
		}
		else if (str[*i] == '"')
		{
			quoted_word = extract_quoted(str, i);
			res = ft_strjoin(res, quoted_word);
		}
		else
			res = ft_strjoin(res, extract_word(str, i));
	}
	res = ft_strjoin(tmp, res);
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
		if (word && word[0] != '\0')
			add_node(head, create_node(word));
		else
			free(word);
	}
	return (*head);
}

int	main(void)
{
	t_node *head;
	char *str;

	char *tests[] = {
		// Variables seules
		"$USER",
		"$HOME",
		"$PWD",
		"$PATH",
		"$NONEXIST",

		// Variables entre quotes
		"'$USER'",
		"\"$USER\"",
		"'$HOME/$USER'",
		"\"$HOME/$USER\"",

		// Variables mélangées avec du texte
		"salut$USER<<$PWD",
		"$USER_machin",
		"$USER123",
		"$HOME/Documents",

		// Variables avec espaces et quotes combinées
		"echo $USER $HOME",
		"echo \"$USER\" '$HOME'",
		"echo start$USERend",

		// Variables dans des commandes
		"ls $HOME",
		"cat \"$PWD/file.txt\"",
		"echo 'Path is $PATH'",
		"echo Mix$USER\"Test\"'$HOME'",

		// Cas spéciaux
		"$?",             // si tu implémentes exit status
		"$0",             // nom du shell
		"$$",             // PID du shell
		"$USER$HOME$PWD", // concaténation directe

		NULL // toujours terminer par NULL
	};
	int i = 0;
	while (tests[i])
	{
		head = NULL;
		printf("=== TEST %d ===\n", i + 1);
		printf("Input: [%s]\n", tests[i]);
		lexer(tests[i], &head);
		print_list(&head);
		clear_nodes(&head);
		printf("\n");
		i++;
	}
	return (0);
	head = NULL;
	str = "echo $HOME$USER$PWD $USER mam miiu";
	lexer(str, &head);
	print_list(&head);
	clear_nodes(&head);
}