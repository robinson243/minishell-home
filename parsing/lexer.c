/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:19:09 by romukena          #+#    #+#             */
/*   Updated: 2025/12/06 12:02:18 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*handle_quote_management(char *tmp, char *str, int *i, char **envp)
{
	char	*quoted_word;
	char	*res;

	res = ft_strdup("");
	while (str[*i] && recognize_token(str, i) == WORD && !is_space(str[*i]))
	{
		if (str[*i] == '\'')
		{
			quoted_word = extract_single_quoted(str, i);
			if (!quoted_word)
				return (free(res), free(tmp), NULL);
			res = ft_strjoin_free(res, quoted_word);
		}
		else if (str[*i] == '"')
		{
			quoted_word = extract_quoted(str, i);
			if (!quoted_word)
				return (free(res), free(tmp), NULL);
			res = ft_strjoin_free(res, quoted_word);
		}
		else
			res = ft_strjoin_free(res, extract_word(str, i, envp));
	}
	res = ft_strjoin_free(tmp, res);
	return (res);
}

char	*build_word(char *input, int *i, int *quoted, char **envp)
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
		else if (recognize_token(input, i) != WORD)
			break ;
		else
			tmp = extract_word(input, i, envp);
		if (!tmp)
			return (free(word), NULL);
		word = ft_strjoin_free(word, tmp);
	}
	return (word);
}

t_node	*lexer(char *input, t_node **head, char **envp)
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
		word = build_word(input, &i, &quoted, envp);
		if (!word)
			return (clear_nodes(head), NULL);
		if (word)
			add_node(head, create_node(word, quoted));
		else
			free(word);
	}
	return (*head);
}
