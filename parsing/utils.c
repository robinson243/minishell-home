/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 16:11:04 by romukena          #+#    #+#             */
/*   Updated: 2025/11/21 14:37:18 by romukena         ###   ########.fr       */
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

void	set_token_type(t_node *node)
{
	if (!node || !node->content)
		return ;
	if (node->quoted == 0 && ft_strcmp(node->content, "|") == 0)
		node->type = PIPE;
	else if (node->quoted == 0 && ft_strcmp(node->content, "<") == 0)
		node->type = REDIR_IN;
	else if (node->quoted == 0 && ft_strcmp(node->content, ">") == 0)
		node->type = REDIR_OUT;
	else if (node->quoted == 0 && ft_strcmp(node->content, ">>") == 0)
		node->type = REDIR_APPEND;
	else if (node->quoted == 0 && ft_strcmp(node->content, "<<") == 0)
		node->type = HEREDOC;
	else
		node->type = WORD;
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

void	print_cmd_list(t_cmd *cmd)
{
	t_redir	*r;
	int		i;

	while (cmd)
	{
		printf("=== Command ===\n");
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
			{
				printf("argv[%d]: %s\n", i, cmd->argv[i]);
				i++;
			}
		}
		r = cmd->redir;
		while (r)
		{
			printf("redir type=%d file=%s\n", r->type, r->file);
			r = r->next;
		}
		printf("pipe_out=%d\n\n", cmd->pipe_out);
		cmd = cmd->next;
	}
}
