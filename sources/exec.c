/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:41:29 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/27 21:13:10 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_tree(t_node *node)
{
	if (!node)
		return ;
	execute_code(node);
	node = node->left;
	node = node->right;
}

void	execute_code(t_node *node)
{
	if (node->type == HEREDOC)
		//heredoc 실행
	else if (node->type == PIPE)
		//pipe
	else if (node->type == REDIR)
		//redir
	else if (node->type == TOKEN)
		//command
}

