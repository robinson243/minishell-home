/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:14:30 by romukena          #+#    #+#             */
/*   Updated: 2025/11/18 12:00:26 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*find_path(char *str, char **envp)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (ft_strncmp(str, envp[i], len) == 0)
		{
			s = ft_strdup(envp[i] + len + 1);
			return (s);
		}
		i++;
	}
	return (NULL);
}

char	*expand_dollar_basic(char *s, int *i, char **envp)
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
	val = find_path(name, envp);
	free(name);
	if (val)
		return (ft_strdup(val));
	else
		return (ft_strdup(""));
}

char	*expand_variables_basic(char *s, char **envp)
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
			tmp = expand_dollar_basic(s, &i, envp);
			res = ft_strjoin_free(res, tmp);
		}
	}
	return (res);
}

t_node	*handle_expands(t_node **head, char **envp)
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
			expanded = expand_variables_basic(tmp->content, envp);
			free(tmp->content);
			tmp->content = expanded;
		}
		tmp = tmp->next;
	}
	return (*head);
}
