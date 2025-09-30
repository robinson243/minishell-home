/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:45:55 by ydembele          #+#    #+#             */
/*   Updated: 2025/09/30 15:56:33 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	env(envp);
// }