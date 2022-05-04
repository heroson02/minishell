/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:17:26 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 21:16:14 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_astree	*create_tree(void)
{
	t_astree	*tree;

	tree = (t_astree *)malloc((sizeof(t_astree)));
	if (tree == 0)
		return (0);
	ft_bzero(tree, sizeof(t_astree));
	return (tree);
}

t_node	*create_node(t_tok	*token)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == 0)
		return (0);
	ft_bzero(node, sizeof(t_node));
	node->data = ft_strdup(token->data);
	node->type = token->type;
	return (node);
}
