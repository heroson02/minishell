/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 12:58:52 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/12 19:02:44 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	*ret;
	size_t			iter;
	unsigned char	val;

	iter = 0;
	ret = (unsigned char *)ptr;
	val = (unsigned char)c;
	while (iter < len)
	{
		*ret = val;
		ret++;
		iter++;
	}
	return (ptr);
}
