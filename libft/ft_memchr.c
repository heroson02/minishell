/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:03:05 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/01 13:40:28 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char		*ustr;
	size_t				idx;
	unsigned char		find;

	find = (unsigned char)c;
	idx = 0;
	ustr = (unsigned char *)str;
	while (idx < n)
	{
		if (ustr[idx] == find)
			return (ustr + idx);
		idx++;
	}
	return (0);
}
