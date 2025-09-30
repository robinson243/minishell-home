/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 12:50:40 by romukena          #+#    #+#             */
/*   Updated: 2025/09/30 13:55:28 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_all(char **av, int ac)
{
	int 	i;
	i = 0;
	while (i < ac)
	{
		free(av[i++]);
	}
	free(av);
}

char **make_line(int ac, char **av)
{
	int	i;
	int	j;
	char	**tab;
	j = 0;
	tab = malloc(sizeof(char *) * (ac + 1));
	if (!tab)
		return (NULL);
	i = 1;
	while (i < ac)
	{
		tab[j] = ft_strdup(av[i]);
		if (!av[i])
		{
			free_all(tab, ac);
			return (NULL);
		}
		j++;
		i++;
	}
	return (tab);
}


int main(int ac, char **av)
{
	char **tab = make_line(ac, av);
	for (int i = 0; i < ac; i++)
	{
		ft_putstr_fd(tab[i], 1);
	}
	
}