/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:51:05 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:05:54 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(t_node *cmd)
{
	t_node	*cur;
	int		nflag;

	nflag = FALSE;
	if (!cmd->left)
	{
		ft_putchar_fd('\n', STDOUT);
		return ;
	}
	cur = cmd->left;
	if (cur->data[0] == '-' && ft_strlen(cur->data) == 2 && cur->data[1] == 'n')
	{
		nflag = TRUE;
		cur = cur->left;
	}
	while (cur)
	{
		ft_putstr_fd(cur->data, STDOUT);
		if (ft_strcmp(cur->data, "") && cur->left)
			ft_putchar_fd(' ', STDOUT);
		cur = cur->left;
	}
	if (nflag == FALSE)
		ft_putchar_fd('\n', STDOUT);
	get_info()->exitcode = 0;
}
