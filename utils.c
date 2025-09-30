/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 16:06:27 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/30 14:25:42 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}
char	*ft_strdup(char	*s)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) + ft_len(s));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*append_char(char *str, char c)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (ft_len(str) + 2));
	if (!new_str)
		return (NULL);
	while (str && str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	free(str);
	return (new_str);
}

int	verif(int c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (0);
		i++;
	}
	return (1);
}

int	ft_lstadd_back(t_node **lst, t_node *new)
{
	t_node	*current;

	if (!lst || !new)
		return (0);
	if (*lst == NULL)
	{
		*lst = new;
		(*lst)->next = NULL;
		return (1);
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	return (1);
}

void	ft_lstclear(t_node **lst)
{
	t_node	*current;

	if (!lst)
		return ;
	current = *lst;
	while (*lst != NULL)
	{
		current = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = current;
	}
	*lst = NULL;
}

t_node	*ft_lstnew(char *str, int types)
{
	t_node	*s;

	s = malloc(sizeof(t_node));
	if (s == NULL)
		return (NULL);
	s->content = ft_strdup(str);
	s->type = types;
	s->next = NULL;
	return (s);
}

void	print_list(t_node *lst)
{
	while (lst)
	{
		printf("content = '%s' , ", lst->content);
		printf("types  :  %d\n", lst->type);
		lst = lst->next;
	}
	printf("NULL\n");
}
