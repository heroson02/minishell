/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:33:51 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/11 19:09:11 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	idx;

	idx = 0;
	dst_size = ft_strlen(dst);
	if (size <= dst_size)
		return (ft_strlen(src) + size);
	while (idx + dst_size + 1 < size && src[idx] != '\0')
	{
		dst[idx + dst_size] = src[idx];
		idx++;
	}
	dst[idx + dst_size] = '\0';
	return (ft_strlen(src) + dst_size);
}
