/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:45:16 by yson              #+#    #+#             */
/*   Updated: 2022/05/13 17:40:48 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_file(t_node *node)
{
	char	*data;

	data = node->data;
	if (data[0] == '-')
	{
		ft_putstr_fd("env: usage: env with no options\n", STDERR);
		get_info()->exitcode = 1;
	}
	else
	{
		ft_putstr_fd("env: usage: env with no args\n", STDERR);
		get_info()->exitcode = 127;
	}
}

void	builtin_env(t_node *cmd)
{
	t_list	*curr;
	t_info	*info;

	info = get_info();
	curr = info->env_list;
	if (cmd->left)
	{
		check_file(cmd->left);
		return ;
	}
	while (curr)
	{
		ft_putstr_fd(((t_enode *)curr->content)->key, STDOUT);
		ft_putchar_fd('=', STDOUT);
		ft_putendl_fd(((t_enode *)curr->content)->value, STDOUT);
		curr = curr->next;
	}
}
