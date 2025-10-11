/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:26:31 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/11 21:15:13 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	my_close(int fd1, int fd2, int fd3, int fd4)
{
	if (fd1 != 1)
		close(fd1);
	if (fd2 != 1)
		close(fd2);
	if (fd3 != 1)
		close(fd3);
	if (fd4 != 1)
		close(fd4);
}

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_strslashjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (res == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		res[j++] = s1[i++];
	res[j++] = '/';
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = 0;
	return (res);
}

char	*get_file(t_node *data, int type, int nb_file)
{
	int		i;
	t_node	*tmp;
	char	*file;

	file = NULL;
	i = 0;
	tmp = data;
	while (tmp)
	{
		if (i == nb_file - 1 && tmp->type == type)
		{
			file = ft_strdup(tmp->content);
			if (!file)
				exit(1);
		}
		else if (tmp->type == type)
			i++;
		tmp = tmp->next;
	}
	return (file);
}