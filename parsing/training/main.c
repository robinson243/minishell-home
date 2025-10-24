/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/24 03:19:46 by romukena         ###   ########.fr       */
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

t_node	*create_node(char *content, int quoted)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->quoted = quoted;
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
		printf("le type quoted %d\n", tmp->quoted);
		if (tmp->content)
			printf("%s\n", tmp->content);
		else
			printf("(null)\n");
		tmp = tmp->next;
	}
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*res;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc(len1 + len2 + 1);
	if (!res)
		return (NULL);
	ft_memcpy(res, s1, len1);
	ft_memcpy(res + len1, s2, len2);
	res[len1 + len2] = '\0';
	free(s1);
	free(s2);
	return (res);
}

char	*expand_dollar_basic(char *s, int *i)
{
	int			start;
	char		*name;
	const char	*val;

	(*i)++;
	if (!ft_isalpha(s[*i]) && s[*i] != '_')
		return (ft_strdup("$"));
	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = ft_substr(s, start, *i - start);
	val = getenv(name);
	free(name);
	return (ft_strdup(val ? val : ""));
}

char	*expand_variables_basic(char *s)
{
	int		i;
	char	*res;
	char	*tmp;
	int		start;

	i = 0;
	res = ft_strdup("");
	while (s[i])
	{
		if (s[i] != '$')
		{
			start = i;
			while (s[i] && s[i] != '$')
				i++;
			tmp = ft_substr(s, start, i - start);
			res = ft_strjoin_free(res, tmp);
		}
		else
		{
			tmp = expand_dollar_basic(s, &i);
			res = ft_strjoin_free(res, tmp);
		}
	}
	return (res);
}

char	*test(char *str)
{
	int	i;
	int	j;
	char	*res;
	char	*tmp;
	res = "";
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (ft_isalnum(s[]))
			{
				/* code */
			}
			
		}
		
		ft_strjoin_char(res, str[i]);
		i++;
	}
	
}




char	*ft_strjoin_char(const char *s, char c)
{
	size_t	len;
	char	*res;

	if (!s)
	{
		res = malloc(2);
		if (!res)
			return (NULL);
		res[0] = c;
		res[1] = '\0';
		return (res);
	}
	len = strlen(s);
	res = malloc(len + 2);
	if (!res)
		return (NULL);
	memcpy(res, s, len);
	res[len] = c;
	res[len + 1] = '\0';
	return (res);
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
	int		quoted;
	char	*word;

	i = 0;
	while (input[i])
	{
		while (input[i] && is_space(input[i]))
			i++;
		if (!input[i])
			break ;
		if (input[i] == '"')
			(word = extract_quoted(input, &i), quoted = 1);
		else if (input[i] == '\'')
			(word = extract_single_quoted(input, &i), quoted = 2);
		else
			(word = extract_word(input, &i), quoted = 0);
		if (word && word[0] != '\0')
			add_node(head, create_node(word, quoted));
		else
			free(word);
	}
	return (*head);
}

t_node	*handle_expands(t_node **head)
{
	t_node	*tmp;
	char	*expanded;

	tmp = *head;
	if (!*head || !head)
		return (NULL);
	while (tmp)
	{
		if (tmp->quoted == 0 || tmp->quoted == 1)
		{
			expanded = expand_variables_basic(tmp->content);
			free(tmp->content);
			tmp->content = expanded;
		}
		tmp = tmp->next;
	}
	return (*head);
}


int	main(void)
{
	t_node	*head;
	char	*str;
	int		i;

	// char *tests[] = {
	// 	// Variables seules
	// 	"$USER",
	// 	"$HOME",
	// 	"$PWD",
	// 	"$PATH",
	// 	"$NONEXIST",
	// 	// Variables entre quotes
	// 	"'$USER'",
	// 	"\"$USER\"",
	// 	"'$HOME/$USER'",
	// 	"\"$HOME/$USER\"",
	// 	// Variables mélangées avec du texte
	// 	"salut$USER<<$PWD",
	// 	"$USER_machin",
	// 	"$USER123",
	// 	"$HOME/Documents",
	// 	// Variables avec espaces et quotes combinées
	// 	"echo $USER $HOME",
	// 	"echo \"$USER\" '$HOME'",
	// 	"echo start$USERend",
	// 	// Variables dans des commandes
	// 	"ls $HOME",
	// 	"cat \"$PWD/file.txt\"",
	// 	"echo 'Path is $PATH'",
	// 	"echo Mix$USER\"Test\"'$HOME'",
	// 	// Cas spéciaux
	// 	"$?",             // si tu implémentes exit status
	// 	"$0",             // nom du shell
	// 	"$$",             // PID du shell
	// 	"$USER$HOME$PWD", // concaténation directe
	// 	NULL // toujours terminer par NULL
	// };
	// i = 0;
	// while (tests[i])
	// {
	// 	head = NULL;
	// 	printf("=== TEST %d ===\n", i + 1);
	// 	printf("Input: [%s]\n", tests[i]);
	// 	lexer(tests[i], &head);
	// 	// handle_expands(&head);
	// 	print_list(&head);
	// 	clear_nodes(&head);
	// 	printf("\n");
	// 	i++;
	// }
	head = NULL;
	str = "start$USERend";
	char *expanded = expand_env(str);
	printf("%s", expanded);
	// lexer(str, &head);
	// print_list(&head);
	// clear_nodes(&head);
	return (0);
}
