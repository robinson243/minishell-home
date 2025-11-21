/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:14:30 by romukena          #+#    #+#             */
/*   Updated: 2025/11/21 15:21:15 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*find_path(char *str, char **envp)
{
	int		i;
	int		len;
	char	*s;
	char	*key;

	i = 0;
	len = ft_strlen(str);
	while (envp[i])
	{
		key = ft_substr(envp[i], 0, ((size_t)ft_strchr(envp[i], '=')
					- (size_t)envp[i]));
		if (!key)
			return (NULL);
		if (ft_strncmp(str, key, ft_strlen(key)) == 0)
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

char	*expand_dollar_segment(char *s, int *i, char **envp, int prv_code)
{
	char	*tmp;

	if (s[*i + 1] == '?')
	{
		*i += 2;
		return (ft_itoa(prv_code));
	}
	tmp = expand_dollar_basic(s, i, envp);
	return (tmp);
}

char	*expand_variables_basic(char *s, char **envp, int prv_code)
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
		}
		else
			tmp = expand_dollar_segment(s, &i, envp, prv_code);
		res = ft_strjoin_free(res, tmp);
	}
	return (res);
}

t_node	*handle_expands(t_node **head, char **envp, int prv_code)
{
	t_node	*tmp;
	char	*expanded;
	char	*status_str;

	tmp = *head;
	if (!*head || !head)
		return (NULL);
	while (tmp)
	{
		set_token_type(tmp);
		if ((tmp->quoted == 0 || tmp->quoted == 1) && tmp->type == WORD)
		{
			expanded = expand_variables_basic(tmp->content, envp, prv_code);
			free(tmp->content);
			tmp->content = expanded;
			if (ft_strcmp(tmp->content, "$?") == 0)
			{
				status_str = ft_itoa(prv_code);
				free(tmp->content);
				tmp->content = status_str;
			}
		}
		tmp = tmp->next;
	}
	return (*head);
}
