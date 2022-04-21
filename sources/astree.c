/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:17:26 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/21 21:39:59 by hyojlee          ###   ########.fr       */
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

int	insert_pipe_heredoc(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	if (!tree)
		return (FALSE);
	cur = tree->root;
	pre = cur;
	while (cur && cur->type == HEREDOC)
	{
		pre = cur;
		cur = cur->left;
	}
	if (!pre)
		tree->root = node;
	else
		pre->left = node;
	node->left = cur;
	return (TRUE);	
}

int	insert_redir(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	if (!tree)
		return (FALSE);
	cur = tree->root;
	pre = cur;
	while (cur)
	{
		pre = cur;
		if (cur->type == TOKEN || cur->type == SQUOTE || cur->type == DQUOTE)
			break ;
		else if (cur->type == PIPE)
			cur = cur->right;
		else
			cur = cur->left;
	}
	if (!pre)
		tree->root = node;
	else if (pre->type == PIPE)
		pre->right = node; //파이프일 떄
	else
		pre->left = node;
	node->left = cur;
	return (TRUE);
}

/*
** pipe가 여러 개 존재하는 경우, 나중에 온 파이프가 위에 위치한다.
** redir 또는 heredoc이 여러 개 존재하는 경우, 나중에 온 친구가 아래에 위치한다.
** 
** 1. 위에서부터 pipe인지 검사하고 오른쪽이 비어있으면 insert
** 2. pipe인데 오른쪽이 채워져있으면 이때 리다이렉션인지 검사하고 마지막 리다이렉션을 찾아 왼쪽으로 이동
**	  -> 마지막 리다이렉션까지 이동 후 왼쪽이 비워져 있으면 거기에 insert, 채워져 있으면 왼쪽 끝까지 이동 후 insert
** 3. heredoc인 경우, pipe와 마찬가지
 */ 
int insert_path(t_astree *tree, t_node *node)	//path와 args에 들어갈 insert 함수
{
	t_node	*cur;
	t_node	*pre;

	if (!tree)
		return (FALSE);
	cur = tree->root;
	pre = cur;
	while (cur)
	{
		pre = cur;
		if (cur->type == PIPE)
			cur = cur->right;
		else
			cur = cur->left;
	}
	if (!pre)
		tree->root = node;
	else if (pre->type == PIPE)
		pre->right = node;
	else
		pre->left = node;
	return (TRUE);
}

// 반드시 리다이렉션이 나오고 호출되기 때문에 루트가 비어있는지 확안헐 필요는 없음
int	insert_filename(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	if (!tree)
		return (FALSE);
	cur = tree->root;
	while (cur) //root는 반드시 채워져 있어야하므로 pre = cur가 while 전에 있을 필요는 없음
	{
		pre = cur;
		if (cur->type == PIPE)
			cur = cur->right;
		else if (cur->type == REDIR)
		{
			if (cur->right)
				cur = cur->left;
			else
				cur = cur->right;
		}
		else
			cur = cur->left;
	}
	if (pre->type == PIPE)
		pre->right = node;
	else
		pre->left = node;
	return (TRUE);
}
