/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:32:08 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/26 16:59:48 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	chk_syntax(t_node *node)
{
	if (!node)
		return (TRUE);
	if (node->type == PIPE)
	{
		if (!node->left || !node->right)
			return (FALSE);
		else if (node->left->type == REDIR &&
				ft_strlen(node->left->data) == 1 && node->left->data[0] == '>')
			return (TRUE);
	}
	else if (node->type == REDIR || node->type == HEREDOC)
	{
		if (!node->right)
			return (FALSE);
	}
	return (chk_syntax(node->left) && chk_syntax(node->right));
}
