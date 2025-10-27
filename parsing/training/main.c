/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/27 17:04:42 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	recognize_token(const char *s, int *i)
{
	if (!s || s[*i] == '\0')
		return (WORD);
	if (s[*i] == '|')
		return (PIPE);
	if (s[*i] == '<')
	{
		if (s[(*i) + 1] == '<')
			return (HEREDOC);
		return (REDIR_IN);
	}
	if (s[*i] == '>')
	{
		if (s[(*i) + 1] == '>')
			return (REDIR_APPEND);
		return (REDIR_OUT);
	}
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
		printf("le type est %d\n", tmp->type);
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
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
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
		ft_putstr_fd("minishell: unexpected EOF near \"\n", 2);
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
		ft_putstr_fd("minishell: unexpected EOF near '\''\n", 2);
		return (NULL);
	}
	res = ft_substr(str, j, (*i - j));
	(*i)++;
	return (res);
}

char	*extract_operator(char *str, int *i)
{
	char	*res;
	int		filter_operator;

	filter_operator = recognize_token(str, i);
	res = NULL;
	if (filter_operator == HEREDOC || filter_operator == REDIR_APPEND)
	{
		res = ft_substr(str, *i, 2);
		*i += 2;
	}
	else
	{
		res = ft_substr(str, *i, 1);
		*i += 1;
	}
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
	if (str[*i] == '$')
		return (extract_dollar(str, i));
	if (recognize_token(str, i) != WORD)
		return (extract_operator(str, i));
	while (str[*i] && !is_space(str[*i]) && str[*i] != '"'
		&& recognize_token(str, i) == WORD && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, j, (*i - j));
	res = handle_quote_management(tmp, str, i);
	return (res);
}

char	*extract_dollar(char *str, int *i)
{
	int		start;
	int		j;
	char	*key;
	char	*res;

	start = *i;
	(*i)++;
	if (str[*i] == '?' || str[*i] == '$' || str[*i] == '0')
	{
		(*i)++;
		return (ft_substr(str, start, 2));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	j = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, j, (*i - j));
	res = getenv(key);
	if (!res)
		res = ft_strdup("");
	else
		res = ft_strdup(res);
	free(key);
	return (res);
}

char	*handle_quote_management(char *tmp, char *str, int *i)
{
	char	*quoted_word;
	char	*res;
	char	*var;

	res = "";
	var = "";
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

char	*mini_double_quoted(char *input, int *i, int *quoted)
{
	char	*tmp;

	tmp = extract_quoted(input, i);
	*quoted = 1;
	return (tmp);
}

char	*mini_single_quoted(char *input, int *i, int *quoted)
{
	char	*tmp;

	tmp = extract_single_quoted(input, i);
	*quoted = 2;
	return (tmp);
}

char	*build_word(char *input, int *i, int *quoted)
{
	char	*word;
	char	*tmp;

	word = ft_strdup("");
	*quoted = 0;
	if (recognize_token(input, i) != WORD)
		return (free(word), extract_operator(input, i));
	while (input[*i] && !is_space(input[*i]))
	{
		if (input[*i] == '"')
			tmp = mini_double_quoted(input, i, quoted);
		else if (input[*i] == '\'')
			tmp = mini_single_quoted(input, i, quoted);
		else
		{
			if (recognize_token(input, i) != WORD)
				break ;
			tmp = extract_word(input, i);
		}
		word = ft_strjoin_free(word, tmp);
	}
	return (word);
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
		word = build_word(input, &i, &quoted);
		if (word && word[0])
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
		set_token_type(tmp);
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

void	set_token_type(t_node *node)
{
	if (!node || !node->content)
		return ;
	if (ft_strcmp(node->content, "|") == 0)
		node->type = PIPE;
	else if (ft_strcmp(node->content, "<") == 0)
		node->type = REDIR_IN;
	else if (ft_strcmp(node->content, ">") == 0)
		node->type = REDIR_OUT;
	else if (ft_strcmp(node->content, ">>") == 0)
		node->type = REDIR_APPEND;
	else if (ft_strcmp(node->content, "<<") == 0)
		node->type = HEREDOC;
	else
		node->type = WORD;
}

int	main(void)
{
	t_node	*head;
	char	*str;
	int		i;

char *tests[] = {
    "echo Bonjour",                          // Commande simple
    "echo \"42 Paris\" 'Piscine C'",        // Double + simple quotes fermées
    "ls -l /tmp | grep txt > out.txt",      // Pipe et redirection
    "echo $USER $HOME $PWD",                 // Variables à expanser (quoted=0)
    "echo \"Mix de$USER et 'quotes'\"",     // Variable dans double quotes, simple quotes littérales
    "echo 'Test $HOME'",                     // Simple quotes, pas d’expansion
    "echo \"Test $HOME\"",                   // Double quotes, expansion
    "echo 'unclosed",                        // Simple quote non fermée
    "echo \"unclosed",                       // Double quote non fermée
    "cat < file.txt > output.txt",           // Redirections
    "echo salut$USER<<$PWD",                 // Variable + heredoc operator
	"echo mix $USER\"test\"'ouf'",
	"cat 'miam'\"ouf\"",
    "echo 'adjacent''quotes'",               // Quotes simples adjacentes
    "echo \"adjacent\"\"double\"",           // Quotes doubles adjacentes
    "echo Mixed$USER\"Test\"'$HOME'",        // Mix quotes et variables
    "ls | grep \"foo\"",                     // Pipe + quote
    "echo \"  spaced text \"",               // Espaces dans quotes doubles
    "echo ''",                              // Empty simple quotes
    "echo \"\"",                            // Empty double quotes
    "echo $USER$HOME$PWD",                  // Variables concaténées
    "export VAR=test; echo $VAR",            // Point important: pas de ; validé, test to see ignoring
    "echo escaped\\$USER",                   // échappement backslash ($ non expansé)
    "echo \"Nested 'quotes' inside\"",       // Quotes imbriquées dans doubles quotes
    "echo 'Nested \"quotes\" inside'",       // Quotes imbriquées dans simples quotes
    "cat file.txt | grep 'pattern'",         // Pipe + quotes
	"cat<file",                              // Redirection collée → mot unique
"cat < file",                             // Redirection séparée → token <
"echo hello>>file",                       // Append collé → mot unique
"echo hello >> file",                      // Append séparé → token >>
"echo hello|grep h",                      // Pipe collé → mot unique
"echo hello | grep h",                     // Pipe séparé → token |
"echo 'single''adjacent'",              // Simple quotes collées
"echo \"double\"\"adjacent\"",          // Double quotes collées
"echo 'mix\"quotes\"inside'",           // Quotes imbriquées simples+ doubles
"echo \"mix'quotes'inside\"",           // Quotes imbriquées doubles+ simples
"echo \"variable$USERinside\"",          // Variable dans double quotes
"echo 'variable$USERinside'", // Variable dans simple quotes (pas expand)
"echo $USER$HOME",                       // Variables concaténées
"echo \"space $USER inside\"",           // Espaces dans double quotes+ variable
"echo '' '' ''",                         // Plusieurs simples quotes vides
"echo \"\" \"\" \"\"",                   // Plusieurs doubles quotes vides
"echo \"nested 'single' and $HOME\"",    // Mix nested + variable
"echo 'nested \"double\" and $HOME'",    // Mix nested + variable non expand
"echo $0 $?",


	NULL
};
	i = 0;
	while (tests[i])
	{
		head = NULL;
		printf("=== TEST %d ===\n", i + 1);
		printf("Input: [%s]\n", tests[i]);
		lexer(tests[i], &head);
		handle_expands(&head);
		print_list(&head);
		clear_nodes(&head);
		printf("\n");
		i++;
	}
	head = NULL;
	// // int k;
	// // k = 0;
	// // str = "start$USERend";
	// // char *expanded = expanded_char(str);
	// // printf("%s", expanded);
	// // // lexer(str, &head);
	// // // print_list(&head);
	// // // clear_nodes(&head);

	return (0);
}
