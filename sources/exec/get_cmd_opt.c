/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:26:58 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:05:55 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	num_of_opt(t_node *node)
{
	int		ret;
	t_node	*tmp;

	ret = 1;
	tmp = node->left;
	while (tmp)
	{
		ret++;
		tmp = tmp->left;
	}
	return (ret);
}

char	**get_cmd_opt(t_node *node)
{
	int		idx;
	char	**opt;
	t_node	*cur;

	idx = 0;
	cur = node;
	opt = (char **)malloc(sizeof(char *) * (num_of_opt(node) + 1));
	while (cur)
	{
		opt[idx] = ft_strdup(cur->data);
		idx++;
		cur = cur->left;
	}
	opt[idx] = 0;
	return (opt);
}
