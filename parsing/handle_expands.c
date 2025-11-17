/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:14:30 by romukena          #+#    #+#             */
/*   Updated: 2025/11/17 13:23:21 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
