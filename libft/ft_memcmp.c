/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 14:45:56 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/11 15:51:09 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	idx = 0;
	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (idx < n)
	{
		if (ptr1[idx] != ptr2[idx])
			break ;
		idx++;
	}
	if (idx == n)
		idx--;
	return (ptr1[idx] - ptr2[idx]);
}
