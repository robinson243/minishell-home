/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:01:15 by romukena          #+#    #+#             */
/*   Updated: 2025/10/09 20:21:43 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	free_all(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/* int	main(int ac, char **av)
{
	char	*line;
	char	*mysentence;
	char	**split_cmd;
	char	*str;
	int		val;
	char	*str;
	char	*str;
	t_cmd	*tmp;

	(void)ac;
	(void)av;
	using_history();
	while ((line = readline("minishell > ")) != NULL)
	{
		mysentence = ft_strdup(line);
		if (!mysentence)
			return (free(line), (0));
		split_cmd = ft_split(mysentence, ' ');
		if (!split_cmd)
			free_all(split_cmd);
		for (int i = 0; split_cmd[i]; i++)
		{
			printf("word %s\n", split_cmd[i]);
		}
		add_history(line);
		free(line);
	}
	clear_history();
	return (0);
} */


void	print_list(t_cmd **head)
{
	t_cmd *tmp;
	if (!head || !*head)
	{
		printf("(liste vide)\n");
		return ;
	}
	tmp = *head;
	while (tmp)
	{
		if (tmp->word)
			printf("%s -> ", tmp->word);
		else
			printf("(null) -> ");
		tmp = tmp->next;
	}
	printf("NULL\n");
}

t_cmd	*create_node(char *str, bool mode)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->word = str;
	new->mode_in_quote = mode;
	new->next = NULL;
	return (new);
}

void	append_node(t_cmd **head, char *str, bool mode)
{
	t_cmd	*new;
	t_cmd	*temp;

	new = create_node(str, mode);
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int	main(void)
{
	t_cmd	*head = NULL;
	int		i;
	bool	mode;
	char	*str;

	i = 0;
	str = "echo \"salut les gens\" ";
	mode = false;
	while (str[i])
	{
		if (str[i] == '"')
			mode = !mode;
		append_node(&head, NULL, mode);
		i++;
	}
	print_list(&head);
	return (0);
}
