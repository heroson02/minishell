/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 14:28:39 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/12 19:06:50 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*sc;
	size_t			idx;

	if (n == 0)
		return (NULL);
	dest = (unsigned char *)dst;
	sc = (unsigned char *)src;
	idx = 0;
	while (idx < n)
	{
		dest[idx] = sc[idx];
		if (sc[idx++] == (unsigned char)c)
			return (&dest[idx]);
	}
	return (NULL);
}
