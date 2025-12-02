/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:17:07 by romukena          #+#    #+#             */
/*   Updated: 2025/12/02 11:07:39 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*extract_quoted(char *str, int *i)
{
	int		j;
	char	*res;

	j = *i + 1;
	(*i)++;
	while (str[*i] && str[*i] != '"')
		(*i)++;
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
		(*i)++;
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

char	*extract_word(char *str, int *i, char **envp)
{
	int		j;
	char	*tmp;
	char	*res;

	while (is_space(str[*i]))
		(*i)++;
	if (!str[*i])
		return (NULL);
	j = *i;
	if (str[*i] == '$' && str[*i + 1] == '"')
		return (handle_locale_string(str, i));
	if (str[*i] == '$' && str[*i + 1] == '\'')
		return (handle_single_locale_string(str, i));
	if (str[*i] == '$')
		return (extract_dollar(str, i, envp));
	if (recognize_token(str, i) != WORD)
		return (extract_operator(str, i));
	while (str[*i] && !is_space(str[*i]) && str[*i] != '"' && str[*i] != '\''
		&& recognize_token(str, i) == WORD && str[*i] != '$')
		(*i)++;
	tmp = ft_substr(str, j, (*i - j));
	res = handle_quote_management(tmp, str, i, envp);
	return (res);
}

char	*extract_dollar(char *str, int *i, char **envp)
{
	int		j;
	char	*key;
	char	*res;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("$?"));
	}
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	j = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, j, (*i - j));
	res = find_path(key, envp);
	if (!res)
		res = ft_strdup("");
	else
		res = ft_strdup(res);
	free(key);
	return (res);
}
