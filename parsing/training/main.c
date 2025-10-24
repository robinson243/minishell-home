/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/24 14:25:33 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int recognize_token(const char *s, int i)
{
    if (!s || s[i] == '\0')
        return WORD;

    if (s[i] == '|')
        return PIPE;

    if (s[i] == '<')
    {
        if (s[i + 1] == '<')
            return HEREDOC;
        return REDIR_IN;
    }
    if (s[i] == '>')
    {
        if (s[i + 1] == '>')
            return REDIR_APPEND;
        return REDIR_OUT;
    }
    return WORD;
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

// char	*ft_strjoin_free(char *s1, char *s2)
// {
// 	char	*res;
// 	size_t	len1;
// 	size_t	len2;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	len1 = ft_strlen(s1);
// 	len2 = ft_strlen(s2);
// 	res = malloc(len1 + len2 + 1);
// 	if (!res)
// 		return (NULL);
// 	ft_memcpy(res, s1, len1);
// 	ft_memcpy(res + len1, s2, len2);
// 	res[len1 + len2] = '\0';
// 	free(s1);
// 	free(s2);
// 	return (res);
// }

// char	*expand_dollar_basic(char *s, int *i)
// {
// 	int			start;
// 	char		*name;
// 	const char	*val;

// 	(*i)++;
// 	if (!ft_isalpha(s[*i]) && s[*i] != '_')
// 		return (ft_strdup("$"));
// 	start = *i;
// 	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
// 		(*i)++;
// 	name = ft_substr(s, start, *i - start);
// 	val = getenv(name);
// 	free(name);
// 	return (ft_strdup(val ? val : ""));
// }

// char	*expand_variables_basic(char *s)
// {
// 	int		i;
// 	char	*res;
// 	char	*tmp;
// 	int		start;

// 	i = 0;
// 	res = ft_strdup("");
// 	while (s[i])
// 	{
// 		if (s[i] != '$')
// 		{
// 			start = i;
// 			while (s[i] && s[i] != '$')
// 				i++;
// 			tmp = ft_substr(s, start, i - start);
// 			res = ft_strjoin_free(res, tmp);
// 		}
// 		else
// 		{
// 			tmp = expand_dollar_basic(s, &i);
// 			res = ft_strjoin_free(res, tmp);
// 		}
// 	}
// 	return (res);
// }


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
	char	*res;
	int		filter_operator;

	filter_operator = recognize_token(str, *i);
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

char	*extract_dollar(char *str, int *i)
{
	int		j;
	char	*key;
	char	*res;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	if (str[*i] == '$' || str[*i] == '0')
	{
		res = ft_substr(str, *i, 1);
		(*i)++;
		return (res);
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
	if (recognize_token(str, *i) != WORD)
		return (extract_operator(str, i));
	while (str[*i] && !is_space(str[*i]) && str[*i] != '"')
	{
		if (recognize_token(str, *i) != WORD)
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
	while (str[*i] && recognize_token(str, *i) == WORD && !is_space(str[*i]))
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
			// expanded = expand_variables_basic(tmp->content);
			free(tmp->content);
			tmp->content = expanded;
		}
		tmp = tmp->next;
	}
	return (*head);
}

static const char *tokname(int t){
    if (t==PIPE) return "PIPE";
    if (t==REDIR_IN) return "REDIR_IN";
    if (t==HEREDOC) return "HEREDOC";
    if (t==REDIR_OUT) return "REDIR_OUT";
    if (t==REDIR_APPEND) return "REDIR_APPEND";
    return "WORD";
}

void test_recognize_token(void)
{
    const char *samples[] = { "|", "<", "<<", ">", ">>", "a", "<a", ">>x", "<< ", "b|c", NULL };
    for (int k=0; samples[k]; k++){
        const char *s = samples[k];
        int i = 0;
        int before = i;
        int type = recognize_token(s, i);
        int after = i; // doit rester égal à before
        printf("input=\"%s\" i_before=%d type=%s i_after=%d\n", s, before, tokname(type), after);
    }
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
	// head = NULL;
	// // int k;
	// // k = 0;
	// // str = "start$USERend";
	// // char *expanded = expanded_char(str);
	// // printf("%s", expanded);
	// // // lexer(str, &head);
	// // // print_list(&head);
	// // // clear_nodes(&head);

	test_recognize_token();
	
	return (0);
}
