/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydembele <ydembele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 20:26:31 by ydembele          #+#    #+#             */
/*   Updated: 2025/10/11 20:28:38 by ydembele         ###   ########.fr       */
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
