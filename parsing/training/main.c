/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/20 07:55:56 by romukena         ###   ########.fr       */
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


char	*go_to_next_dollar(char *str, int *i)
{
	int	j;
	char	*tmp;
	char	*res;
	char	*dest;

	j = *i;
	dest = "";
	while ()
	{
		/* code */
	}
	
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
		if (str[*i] == '$')
		{
			tmp = handle_dollar_management(str, i);
			dollar_string = ft_strjoin(dollar_string, tmp);
		}
		if (recognize_token(str, i) != WORD)
			return (ft_substr(str, j, (*i - j)));
		(*i)++;
	}
	tmp = ft_substr(str, j, (*i - j));
	res = handle_quote_management(tmp, str, i);
	return (res);
}

char	*handle_dollar_management(char *str, int *i)
{
	int	j;
	char	*tmp;
	char	*res;
	char	*dest;
	(*i)++;
	j = *i;
	dest = "";
	while (str[*i] && recognize_token(str, i) == WORD && !is_space(str[*i]) && str[*i] != '$')
	{
		(*i)++;
	}
	tmp = ft_substr(str, j, (*i - j));
	res = ft_strdup(getenv(tmp));
	dest = ft_strjoin(dest, res);
	printf("%c", str[*i]);
	return (dest);
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

	t_node	*head;
	// char	*tests[] = {
	// 	"echo salut",
	// 	"ls",
	// 	"pwd",
	// 	"exit",
	// 	"echo      salut      les    gens",
	// 	"ls        -l",
	// 	"echo \"salut les gens\"",
	// 	"echo 'salut les gens'",
	// 	"echo \"bonjour 'tout' le monde\"",
	// 	"echo 'bonjour \"tout\" le monde'",
	// 	"echo \"a'b'c\"",
	// 	"echo 'a\"b\"c'",
	// 	"echo salut > out.txt",
	// 	"cat < in.txt",
	// 	"cat < in.txt > out.txt",
	// 	"echo salut >> out.txt",
	// 	"echo salut > out.txt > out2.txt",
	// 	"ls | wc -l",
	// 	"ls -l | grep minishell",
	// 	"cat in.txt | grep salut | wc -l",
	// 	"echo \"salut | les gens\"",
	// 	"echo salut | echo bonjour",
	// 	"echo \"salut\" > out.txt | cat -e",
	// 	"cat << EOF",
	// 	"echo \"salut\" 'les' \"gens\" > file.txt | cat file.txt",
	// 	"|",
	// 	"||",
	// 	">",
	// 	">>",
	// 	"<",
	// 	"<<",
	// 	"| echo salut",
	// 	"echo salut |",
	// 	"echo \"salut",
	// 	"echo 'salut",
	// 	NULL
	// };
	// int	i = 0;

	// while (tests[i])
	// {
	// 	head = NULL;
	// 	printf("=== TEST %d ===\n", i + 1);
	// 	printf("Input: [%s]\n", tests[i]);
	// 	lexer(tests[i], &head);
	// 	print_list(&head);
	// 	clear_nodes(&head);
	// 	printf("\n");
	// 	i++;
	// }
	// return (0);
	head = NULL;
	char *str = "echo $HOME$USER$PWD $USER mam miiu";
	lexer(str, &head);
	print_list(&head);
	clear_nodes(&head);

	// printf("%s\n", getenv("HOME"));
	// printf("%s\n", getenv("USER"));
	// printf("%s\n", getenv("PWD"));

	// "/home/romukena,
	// romukena,
	// /home/romukena/Documents/minishell-home/parsing/training"
}
