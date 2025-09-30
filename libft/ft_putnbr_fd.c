/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romukena <romukena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:36:04 by romukena          #+#    #+#             */
/*   Updated: 2025/04/12 16:22:58 by romukena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr_fd(n / 10, fd);
	ft_putchar_fd((n % 10 + '0'), fd);
}

/* 
int main(void)
{
    int fd = open("test_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return 1;

    ft_putnbr_fd(42, fd);        // Écrit : 42
    write(fd, "\n", 1);

    ft_putnbr_fd(-12345, fd);    // Écrit : -12345
    write(fd, "\n", 1);

    ft_putnbr_fd(0, fd);         // Écrit : 0
    write(fd, "\n", 1);

    ft_putnbr_fd(2147483647, fd); // Écrit : 2147483647 (INT_MAX)
    write(fd, "\n", 1);

    ft_putnbr_fd(-2147483648, fd); // Écrit : -2147483648 (INT_MIN)
    write(fd, "\n", 1);

    close(fd);

    // Lecture du fichier pour vérification
    char buffer[1024];
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
} */