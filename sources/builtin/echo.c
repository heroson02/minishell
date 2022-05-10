/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:51:05 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/10 14:37:49 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(t_node *cmd)
{
	t_node	*cur;
	int		nflag;
	t_info	*info;

	info = get_info();
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
			ft_putchar_fd(' ', STDOUT); // printf(" ");
		cur = cur->left;
	}
	if (nflag == FALSE)
		ft_putchar_fd('\n', STDOUT);
		// printf("\n");
	info->exitcode = 0;
}