/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 13:02:21 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/01 13:32:19 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	char		*s;
	long long	ret;
	long long	flag;

	s = (char *)str;
	ret = 0;
	flag = 1;
	while (ft_isblank(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			flag *= -1;
	while (ft_isdigit(*s))
	{
		ret = ret * 10 + *s - '0';
		if (ret < 0)
		{
			if (flag < 0)
				return (0);
			else
				return (-1);
		}
		s++;
	}
	return (ret * flag);
}
