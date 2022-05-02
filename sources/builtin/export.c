/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yunslee <yunslee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:11:53 by yson              #+#    #+#             */
/*   Updated: 2022/04/30 16:36:37 by yunslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_info *info, char *data)
{
	t_enode *node;
	t_list	*cur;

	if (data[0] == '=')
	{
		printf("bash: export: '%s': not a valid identifier\n", data);
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

// void	ft_export(t_info *info, char *data)
// {
// 	t_enode *node;
// 	t_list	*list;

// 	if (data[0] == '=')
// 	{
// 		printf("bash: export: '%s': not a valid identifier\n", data);
// 		return ;
// 	}
// 	if (!ft_strchr(data, '='))
// 		return ;
// 	list = info->env_list;
// 	node = new_enode(data);
// 	printf("\033[31m%d\033[0m\n", get_env(info, node->key)[0]);
// 	if (get_env(info, node->key)[0])
// 	{
// 		while (list)
// 		{
// 			if (!ft_strcmp(node->key, ((t_enode *)list->content)->key))
// 			{
// 				free_enode(list->content);
// 				list->content = node;
// 			}
// 			list = list->next;
// 		}
// 	}
// 	else
// 		ft_lstadd_back(&(info->env_list), ft_lstnew(new_enode(data)));
// }

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
