/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:14:30 by romukena          #+#    #+#             */
/*   Updated: 2025/12/10 15:24:15 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*find_path(char *str, char **envp)
{
	int		i;
	char	*eq_pos;
	char	*s;

	if (!str || !envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (!eq_pos)
		{
			i++;
			continue ;
		}
		if (ft_strncmp(str, envp[i], eq_pos - envp[i]) == 0 && (size_t)(eq_pos
			- envp[i]) == ft_strlen(str))
		{
			s = ft_strdup(eq_pos + 1);
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
	char	*val;

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
		return ((char *)val);
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

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		set_token_type(tmp);
		handle_dollar_and_status(tmp, envp, prv_code);
		handle_tilde(tmp, envp);
		tmp = tmp->next;
	}
	return (*head);
}
