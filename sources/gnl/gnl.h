/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:53:43 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 20:33:31 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include <stdlib.h>
# include <unistd.h>
# include "../../libft/libft.h"

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 500
# endif

int		get_next_line(int fd, char **line);

/*
** gnl_utils.c
*/
char	*gnl_strjoin(char *s1, char *s2, int *flag);
char	*gnl_strdup(char *s1, int *flag);

#endif