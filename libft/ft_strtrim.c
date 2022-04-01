/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 15:33:23 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/02 22:15:07 by lhj-unix         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isin(char c, char const *set)
{
	while (*set)
		if (*set++ == c)
			return (1);
	return (0);
}

int	ft_idx1(char const *s1, char const *set)
{
	int	idx;

	idx = 0;
	while (s1[idx] != '\0')
	{
		if (!ft_isin(s1[idx], set))
			break ;
		idx++;
	}
	return (idx);
}

int	ft_idx2(char const *s1, char const *set)
{
	int	idx;

	idx = ft_strlen(s1) - 1;
	while (idx >= 0)
	{
		if (!ft_isin(s1[idx], set))
			break ;
		idx--;
	}
	if (idx == -1)
		idx = ft_strlen(s1) - 1;
	return (idx);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		idx[3];
	int		msize;

	if (!s1)
		return (0);
	idx[0] = ft_idx1(s1, set);
	idx[1] = ft_idx2(s1, set);
	idx[2] = 0;
	if (!set)
		return ((char *)s1);
	msize = idx[1] - idx[0] + 2;
	if (s1[0] == '\0')
		msize = 1;
	ret = (char *)malloc(sizeof(char) * msize);
	if (!ret)
		return (0);
	ret[0] = '\0';
	while (idx[0] <= idx[1])
		ret[idx[2]++] = s1[idx[0]++];
	ret[idx[2]] = '\0';
	return (ret);
}
