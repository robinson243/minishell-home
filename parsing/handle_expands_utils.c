/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:27:39 by romukena          #+#    #+#             */
/*   Updated: 2025/11/21 17:28:42 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*expand_tilde(char *s, char **envp)
{
	char	*home;
	char	*new;

	if (!s || s[0] != '~')
		return (s);
	home = find_path("HOME", envp);
	if (!home)
		return (s);
	new = ft_strjoin(home, s + 1);
	free(home);
	return (new);
}

void	handle_dollar_and_status(t_node *tmp, char **envp, int prv_code)
{
	char	*expanded;
	char	*status_str;

	if ((tmp->quoted == 0 || tmp->quoted == 1) && tmp->type == WORD)
	{
		expanded = expand_variables_basic(tmp->content, envp, prv_code);
		if (expanded != tmp->content)
		{
			free(tmp->content);
			tmp->content = expanded;
		}
		if (ft_strcmp(tmp->content, "$?") == 0)
		{
			status_str = ft_itoa(prv_code);
			free(tmp->content);
			tmp->content = status_str;
		}
	}
}

void	handle_tilde(t_node *tmp, char **envp)
{
	char	*tilde_expanded;

	if (tmp->quoted == 0 && tmp->type == WORD)
	{
		tilde_expanded = expand_tilde(tmp->content, envp);
		if (tilde_expanded != tmp->content)
		{
			free(tmp->content);
			tmp->content = tilde_expanded;
		}
	}
}
