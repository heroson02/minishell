/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:17:26 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/19 21:16:30 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_astree	*create_tree(void)
{
	t_astree	*tree;

	tree = (t_astree *)malloc((sizeof(t_astree)));
	if (tree == 0)
		return (0);
	ft_bzero(tree, sizeof(t_astree));
	return (tree);
}

t_node	*create_node(t_data data, t_type type)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == 0)
		return (0);
	ft_bzero(node, sizeof(t_node));
	node->data = data;
	node->type = type;
	return (node);
}

int	insert_pipe(t_astree *tree, t_node	*node)
{
	t_node	*cur;
	t_node	*pre;

	if (!tree || !(tree->root))
		return (FALSE);
	pre = 0;
	cur = tree->root;
	while (cur && cur->type == PIPE)
	{
		pre = cur;
		cur = cur->right;
	}
	node->left = cur;
	pre->right = node;
	return (TRUE);
}

int	insert_redir(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	if (!tree || !(tree->root))
		return (FALSE);
	pre = 0;
	cur = tree->root;
	while (cur && cur->type == PIPE && cur->type == REDIR)
	{
		pre = cur;
		cur = cur->right;
	}
	node->left = cur;
	pre->right = node;
	return (TRUE);
}

int	insert_token(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	if (!tree || !(tree->root))
		return (FALSE);
	pre = 0;
	cur = tree->root;
	while (cur->right)
		cur = cur->right;
	if (cur->type == PIPE || cur->type == REDIR)
	{
		cur->right = node;
		return (TRUE);
	}
	while (cur->left)
		cur = cur->left;
	cur->left = node;
	return (TRUE);
}
