/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 15:11:25 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/01 13:41:22 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_writenum(int n, int fd)
{
	char	s;

	if (n > 9)
	{
		ft_writenum(n / 10, fd);
		ft_writenum(n % 10, fd);
	}
	else
	{
		s = n + '0';
		write(fd, &s, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
	{
		write(fd, "-", 1);
		if (n == -2147483648)
		{
			write(fd, "2", 1);
			n = -147483648;
		}
		n *= -1;
	}
	ft_writenum(n, fd);
}
