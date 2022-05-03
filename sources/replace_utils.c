/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:37:13 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/03 18:14:20 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	join_str(char **before, char *data, int *start, int end)
{
	char	*origin;
	char	*new_str;

	if (end - *start > 0)
	{
		new_str = ft_substr(data, *start, end - *start);
		origin = *before;
		*before = ft_strjoin(*before, new_str);
		free(new_str);
		new_str = 0;
		free(origin);
		origin = 0;
	}
	*start = end + 1;
}

void	join_envp(char **before, char *env, int *start, int *end)
{
	char	*origin;

	if (*end - *start > 0)
	{
		origin = *before;
		*before = ft_strjoin(*before, env);
		free(env);
		env = 0;
		free(origin);
		origin = 0;
	}
	*start = *end;
	*end -= 1;
}

void	find_end_pos(char *data, int *end)
{
	char	cur;
	int		new_end;

	new_end = *end;
	cur = data[new_end];
	while (cur && cur != '\'' && cur != '\"' && !ft_isblank(cur)
		&& cur != '$')
		cur = data[(++new_end)];
	*end = new_end;	
}