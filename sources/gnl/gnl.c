/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:58:12 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 18:50:40 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./gnl.h"
#include <stdio.h>
#include <fcntl.h>

static int	isin_newline(char *str)
{
	int	idx;

	idx = 0;
	if (!str)
		return (-1);
	while (str[idx])
		if (str[idx++] == '\n')
			return (idx - 1);
	return (-1);
}

static int	have_newline(char **tmp, char **line, int idx)
{
	char	*box;
	int		flag;

	flag = 0;
	(*tmp)[idx] = '\0';
	*line = gnl_strdup(*tmp, &flag);
	if (flag)
		return (-1);
	box = gnl_strdup(*tmp + idx + 1, &flag);
	if (flag)
		return (-1);
	free(*tmp);
	*tmp = gnl_strdup(box, &flag);
	if (flag)
		return (-1);
	free(box);
	return (1);
}

static int	nbytes_zero(char **tmp, char **line)
{
	int	flag;
	int	idx;

	flag = 0;
	idx = isin_newline(*tmp);
	if (idx >= 0)
		return (have_newline(tmp, line, idx));
	if (!*tmp)
	{
		*tmp = (char *)malloc(sizeof(char) * 1);
		if (!*tmp)
			return (-1);
		*tmp[0] = '\0';
	}
	*line = gnl_strdup(*tmp, &flag);
	if (flag)
		return (-1);
	free(*tmp);
	*tmp = 0;
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*tmp[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			idx;
	ssize_t		nbytes;
	int			flag;

	flag = 0;
	if (BUFFER_SIZE < 1)
		return (-1);
	nbytes = read(fd, buf, BUFFER_SIZE);
	while (nbytes > 0)
	{
		buf[nbytes] = '\0';
		tmp[fd] = gnl_strjoin(tmp[fd], buf, &flag);
		if (flag)
			return (-1);
		idx = isin_newline(tmp[fd]);
		if (idx >= 0)
			return (have_newline(&tmp[fd], line, idx));
	}
	if (nbytes == 0)
		return (nbytes_zero(&tmp[fd], line));
	return (-1);
}
