/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:21:26 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/01 14:10:48 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	idx;
	size_t	idx2;

	idx = 0;
	idx2 = 0;
	if (!s1 || !s2)
		return (0);
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	while (idx < ft_strlen(s1))
	{
		ret[idx] = s1[idx];
		idx++;
	}
	while (idx2 < ft_strlen(s2))
	{
		ret[idx + idx2] = s2[idx2];
		idx2++;
	}
	ret[idx + idx2] = '\0';
	return (ret);
}
