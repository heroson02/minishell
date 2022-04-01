/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 20:09:50 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/13 11:05:20 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char			*s;
	char			*ret;
	unsigned char	find;
	int				flag;

	s = (char *)str;
	ret = 0;
	find = (unsigned char)c;
	flag = 1;
	while (*s)
	{
		if ((unsigned char)*s++ == find)
		{
			ret = s - 1;
			flag = 0;
		}
	}
	if ((unsigned char)*s == find && flag)
		return (s);
	return (ret);
}
