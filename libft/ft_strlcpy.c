/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:29:29 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/09 13:02:25 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	ret;

	ret = 0;
	if (!dst || !src)
		return (0);
	while (ret + 1 < dstsize && src[ret] != '\0')
	{
		dst[ret] = src[ret];
		ret++;
	}
	if (dstsize != 0)
		dst[ret] = '\0';
	while (src[ret] != '\0')
		ret++;
	return (ret);
}
