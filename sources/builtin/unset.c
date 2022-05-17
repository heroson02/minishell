/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:18 by yson              #+#    #+#             */
/*   Updated: 2022/05/17 16:54:26 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_no_args(void)
{
	ft_putendl_fd("unset: usage: unset with no option", STDERR);
	get_info()->exitcode = 2;
}

static void	ft_unset(t_info *info, char *target)
{
	t_list	*pre;
	t_list	*cur;

	pre = info->env_list;
	cur = pre;
	if (target[0] == '-')
	{
		unset_no_args();
		return ;
	}
	while (cur)
	{
		if (!ft_strcmp(target, ((t_enode *)cur->content)->key))
			break ;
		pre = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	if (pre == cur)
		info->env_list = cur->next;
	else
		pre->next = cur->next;
	ft_lstdelone(cur, free_enode);
}

void	builtin_unset(t_node *cmd)
{
	t_node	*node;
	t_info	*info;

	info = get_info();
	node = cmd->left;
	while (node)
	{
		ft_unset(info, node->data);
		node = node->left;
	}
}
