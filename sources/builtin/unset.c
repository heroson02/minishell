/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:55:18 by yson              #+#    #+#             */
/*   Updated: 2022/05/18 13:32:40 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_error(char *data)
{
	ft_putstr_fd("minishell: unset: \'", STDERR);
	ft_putstr_fd(data, STDERR);
	ft_putendl_fd("\': not a valid identifier", STDERR);
	get_info()->exitcode = 1;
}

static int	key_validation(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '=' || ft_isdigit(key[0]))
		return (0);
	while (key[i])
	{
		if (ft_isdigit(key[i]) || ft_isalpha(key[i]) || key[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

static void	ft_unset(t_info *info, char *target)
{
	t_list	*pre;
	t_list	*cur;

	pre = info->env_list;
	cur = pre;
	if (!key_validation(target))
	{
		unset_error(target);
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

	node = cmd->left;
	get_info()->exitcode = 0;
	if (node && node->data[0] == '-')
	{
		ft_putstr_fd("minishell: unset: ", STDERR);
		ft_putchar_fd(node->data[0], STDERR);
		ft_putchar_fd(node->data[1], STDERR);
		ft_putendl_fd(": invalid option", STDERR);
		ft_putendl_fd("unset: usage: unset with no option", STDERR);
		get_info()->exitcode = 2;
		return ;
	}
	while (node)
	{
		ft_unset(get_info(), node->data);
		node = node->left;
	}
}
