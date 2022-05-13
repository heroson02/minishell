/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:11:53 by yson              #+#    #+#             */
/*   Updated: 2022/05/13 17:38:12 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_no_args(void)
{
	t_list	*lst;

	lst = get_info()->env_list;
	while (lst)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(((t_enode *)lst->content)->key, STDOUT);
		ft_putstr_fd("=\"", STDOUT);
		ft_putstr_fd(((t_enode *)lst->content)->value, STDOUT);
		ft_putendl_fd("\"", STDOUT);
		lst = lst->next;
	}
}

static void	ft_export(t_info *info, char *data)
{
	t_enode	*node;
	t_list	*cur;

	if (data[0] == '=')
	{
		printf("minishell: export: ", STDERR);
		ft_putstr_fd(data, STDERR);
		ft_putendl_fd(": not a valid identifier", STDERR);
		info->exitcode = 1;
		return ;
	}
	if (!ft_strchr(data, '='))
		return ;
	cur = info->env_list;
	node = new_enode(data);
	while (cur && ft_strcmp(node->key, ((t_enode *)cur->content)->key))
		cur = cur->next;
	if (!cur)
		ft_lstadd_back(&(info->env_list), ft_lstnew(node));
	else
	{
		free_enode(cur->content);
		cur->content = node;
	}
}

void	builtin_export(t_node *cmd)
{
	t_node	*node;
	t_info	*info;

	info = get_info();
	node = cmd->left;
	if (!node)
	{
		export_no_args();
		return ;
	}
	while (node)
	{
		ft_export(info, node->data);
		node = node->left;
	}
}
