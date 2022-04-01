/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 21:57:03 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/01 14:17:45 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_of_arg(char const *s, char c)
{
	int		cnt;
	int		idx;

	cnt = 1;
	idx = 0;
	while (s[idx] != '\0')
	{
		if (!idx && s[idx] != c)
			cnt++;
		if (s[idx++] == c)
			if (s[idx] != c && s[idx])
				cnt++;
	}
	return (cnt);
}

static int	ft_strlench(char const *s, char c)
{
	int	idx;

	idx = 0;
	while (s[idx] != '\0' && s[idx] != c)
		idx++;
	return (idx);
}

static void	ft_free(char **s, int i)
{
	int	idx;

	idx = 0;
	while (idx < i)
		free(s[idx++]);
	free(s);
}

static int	ft_malloc(char **ret, int *idx, int len, char const *s)
{
	ret[*idx] = (char *)malloc(len + 1);
	if (!ret[idx[0]])
	{
		ft_free(ret, idx[0]);
		return (0);
	}
	idx[1] = 0;
	while (idx[1] < len)
		ret[idx[0]][idx[1]++] = s[idx[2]++];
	ret[idx[0]++][idx[1]] = '\0';
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		idx[3];
	int		len;

	idx[0] = 0;
	idx[2] = 0;
	if (!s)
		return (0);
	ret = (char **)malloc(sizeof(char *) * num_of_arg(s, c));
	if (!ret)
		return (0);
	while (idx[0] < num_of_arg(s, c) && s[idx[2]] != '\0')
	{
		len = ft_strlench(&s[idx[2]], c);
		if (!len)
		{
			idx[2]++;
			continue ;
		}
		if (!ft_malloc(ret, idx, len, s))
			return (0);
	}
	ret[num_of_arg(s, c) - 1] = 0;
	return (ret);
}
