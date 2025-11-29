/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_star.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 01:50:07 by romukena          #+#    #+#             */
/*   Updated: 2025/11/29 02:03:05 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* expand_star.c */
#include "exec.h"

/*Compte combien de fichiers matchent "*" */
static int	count_files(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	dir = opendir(".");
	if (!dir)
		return (0);
	count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

/* Remplit le tableau avec les fichiers */
static int	fill_expanded(char **expanded, int idx)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
		return (idx);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
		{
			expanded[idx] = ft_strdup(entry->d_name);
			idx++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (idx);
}

/* Compte total args après expansion */
static int	count_total(char **argv)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (argv[i])
	{
		if (argv[i][0] == '*' && argv[i][1] == '\0')
			count += count_files();
		else
			count++;
		i++;
	}
	return (count);
}

/* Expande les "*" dans argv */
char	**expand_star_argv(char **argv)
{
	char	**expanded;
	int		total;
	int		i;
	int		j;

	if (!argv || !argv[0])
		return (argv);
	total = count_total(argv);
	expanded = malloc(sizeof(char *) * (total + 1));
	if (!expanded)
		return (argv);
	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] == '*' && argv[i][1] == '\0')
			j = fill_expanded(expanded, j);
		else
			expanded[j++] = ft_strdup(argv[i]);
		i++;
	}
	expanded[j] = NULL;
	return (expanded);
}
