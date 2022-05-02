/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 16:51:05 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/28 18:55:27 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_echo(t_info *info, t_node *cmd)
{
	t_node	*cur;
	int		nflag;

	nflag = FALSE;
	if (!cmd->left)
	{
		printf("\n");
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
		printf("%s", cur->data);
		if (ft_strcmp(cur->data, "") && cur->left)
			printf(" ");
		cur = cur->left;
	}
	if (nflag == FALSE)
		printf("\n");
	info->exitcode = 0;
}