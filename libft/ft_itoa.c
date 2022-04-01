/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 14:11:40 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/01 13:36:19 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digit(int n)
{
	int	dgt;

	dgt = 1;
	if (n < 0)
	{
		if (n == -2147483648)
			return (11);
		dgt++;
		n *= -1;
	}
	while (n > 9)
	{
		n = n / 10;
		dgt++;
	}
	return (dgt);
}

static void	ft_fillitoa(char *s, int n, int idx, int lidx)
{
	if (n > 9)
	{
		ft_fillitoa(s, n % 10, idx, lidx);
		ft_fillitoa(s, n / 10, ++idx, lidx);
	}
	else
	{
		s[lidx - idx] = n + '0';
		return ;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	int		lidx;

	ret = (char *)malloc(ft_digit(n) + 1);
	if (!ret)
		return (0);
	lidx = ft_digit(n);
	ret[lidx] = '\0';
	if (n < 0)
	{
		ret[0] = '-';
		if (n == -2147483648)
		{
			ret[1] = '2';
			n = -147483648;
		}
		n *= -1;
	}
	ft_fillitoa(ret, n, 0, lidx - 1);
	return (ret);
}
