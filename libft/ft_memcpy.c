/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:28:39 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/11 15:47:12 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sc;
	size_t			idx;

	if (!src && !dst)
		return (0);
	dest = (unsigned char *)dst;
	sc = (unsigned char *)src;
	idx = 0;
	while (idx < n)
	{
		dest[idx] = sc[idx];
		idx++;
	}
	return (dst);
}
