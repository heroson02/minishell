/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:55:57 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 18:42:52 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl.h"

size_t	ft_strlen(char *str)
{
	int idx;

	idx = 0;
	while (*str++)
		idx++;
	return (idx);
}

static void	gnl_strlcat(char *ret, char *s1, char *s2)
{
	size_t	dst_size;
	size_t	idx;
	size_t	idx2;

	idx = 0;
	idx2 = 0;
	dst_size = ft_strlen(ret);
	while (s1[idx] != '\0')
	{
		ret[idx + dst_size] = s1[idx];
		idx++;
	}
	ret[idx + dst_size] = '\0';
	free(s1);
	dst_size += idx;
	while (s2[idx2] != '\0')
	{
		ret[idx2 + dst_size] = s2[idx2];
		idx2++;
	}
	ret[idx2 + dst_size] = '\0';
}

char	*gnl_strjoin(char *s1, char *s2, int *flag)
{
	char	*ret;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
	{
		ret = gnl_strdup(s2, flag);
	}
	else if (!s2)
		ret = s1;
	else
	{
		ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (!ret)
		{
			*flag = 1;
			free(s1);
			return (0);
		}
		ret[0] = '\0';
		gnl_strlcat(ret, s1, s2);
	}
	return (ret);
}

char	*gnl_strdup(char *s1, int *flag)
{
	char	*ret;
	int		i;

	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!ret)
	{
		*flag = 1;
		free(s1);
		return (0);
	}
	i = -1;
	while (s1[++i] != '\0')
		ret[i] = s1[i];
	ret[i] = '\0';
	return (ret);
}
