/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 14:00:52 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/04 14:27:54 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"

int	is_nl(char *args)
{
	int	j;

	j = 1;
	if (args[0] == '-')
	{
		while (args[j] && args[j] == 'n')
			j++;
		if (args[j] == 0)
			return (1);
	}
	return (0);
}

int	ft_echo(char **args, t_globale *data)
{
	int	j;
	int	i;
	int	nl;

	i = 0;
	j = 1;
	nl = 1;
	if (args[0] && is_nl(args[0]))
	{
		i = 1;
		nl = 0;
	}
	if (ft_strncmp(args[0], "$?", INT_MAX) == 0)
		printf("%d", data->exit_code);
	else
	{
		while (args[i])
		{
			write(1, args[i], ft_strlen(args[i]));
			if (args[i + 1])
				write(1, " ", 1);
			i++;
		}
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

// int	main(int ac, char **av)
// {
// 	ft_echo(av + 2);
// }
