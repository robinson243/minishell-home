/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:53:30 by romukena          #+#    #+#             */
/*   Updated: 2025/04/12 16:31:20 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0 || !s)
		return ;
	while (s[i])
		ft_putchar_fd(s[i++], fd);
}

/* int main(void)
{
    int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return 1;

    // Tests pour ft_putstr_fd
    ft_putstr_fd("Hello, world!", fd);
    write(fd, "\n", 1);

    ft_putstr_fd("", fd);
    write(fd, "\n", 1);

    ft_putstr_fd("Test avec\nretour ligne", fd);
    write(fd, "\n", 1);

    ft_putstr_fd("Fin des tests", fd);
    write(fd, "\n", 1);

    close(fd);

    // Lecture du fichier pour vérification
    char buffer[2048];
    fd = open("test_output.txt", O_RDONLY);
    if (fd == -1)
        return 1;

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read >= 0)
    {
        buffer[bytes_read] = '\0';
        write(1, buffer, bytes_read);
    }

    close(fd);
    return 0;
}
 */