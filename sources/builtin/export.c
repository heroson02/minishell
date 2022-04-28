/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:11:53 by yson              #+#    #+#             */
/*   Updated: 2022/04/28 18:53:49 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_info *info, char *data)
{
	t_enode *node;
	t_list	*list;

	if (data[0] == '=')
	{
		printf("bash: export: '%s': not a valid identifier\n", data);
		return ;
	}
	if (!ft_strchr(data, '='))
		return ;
	list = info->env_list;
	node = new_enode(data);
	if (get_env(info, node->key)[0])
	{
		while (list)
		{
			if (!ft_strcmp(node->key, ((t_enode *)list->content)->key))
			{
				free_enode(list->content);
				list->content = node;
			}
			list = list->next;
		}
	}
	else
		ft_lstadd_back(&info->env_list, ft_lstnew(new_enode(data)));
}

void	builtin_export(t_info *info, t_node *cmd)
{
	t_node	*node;

	node = cmd->left;
	while (node)
	{
		ft_export(info, node->data);
		node = node->left;
	}
}
