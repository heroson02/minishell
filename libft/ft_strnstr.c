/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 20:11:09 by hyojlee           #+#    #+#             */
/*   Updated: 2021/05/11 19:24:58 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *org, const char *sub, size_t len)
{
	char	*origin;
	char	*find;
	size_t	i;
	size_t	j;

	i = 0;
	origin = (char *)org;
	find = (char *)sub;
	if (!*find)
		return (origin);
	while (i < len && origin[i])
	{
		j = 0;
		if (origin[i] == find[j])
		{
			while (origin[i + j] == find[j] && i + j < len)
			{
				if (find[j + 1] == '\0')
					return (&origin[i]);
				j++;
			}
		}
		i++;
	}
	return (0);
}
