/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 16:44:02 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/05 14:09:26 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*sc;
	size_t			idx;

	if (!dst && !src)
		return (0);
	idx = -1;
	dest = (unsigned char *)dst;
	sc = (unsigned char *)src;
	if (sc >= dest)
	{
		while (++idx < len)
			dest[idx] = sc[idx];
	}
	else
	{
		idx = len;
		while (idx > 0)
		{
			dest[idx - 1] = sc[idx - 1];
			idx--;
		}
	}
	return (dst);
}
