/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:56:28 by ydembele          #+#    #+#             */
/*   Updated: 2025/11/03 16:12:03 by ydembele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../exec/exec.h"
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int	ft_pwd(void)
{
	char	path[1024];

	if (getcwd(path, 1024))
	{
		printf("%s\n", path);
		return (0);
	}
	else
		return (1);
}

// int	main()
// {
// 	ft_pwd();
// }
