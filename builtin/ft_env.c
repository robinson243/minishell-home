/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:45:55 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/20 12:58:41 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	env(char **env, char **commande)
{
	int	i;

	i = 0;
	if (commande[1])
	{
		write(2, "env: too many arguments\n", 25);
		return (1);
	}
	if (!env)
		return (1);
	while (env[i])
		printf("%s\n", env[i++]);
	return (0);
}
