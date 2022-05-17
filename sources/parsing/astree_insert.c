/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:07:48 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/17 19:30:04 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	insert_pipe_heredoc(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	cur = tree->root;
	pre = cur;
	while (cur && cur->type == HEREDOC)
	{
		pre = cur;
		cur = cur->left;
	}
	if (!pre || pre == cur)
		tree->root = node;
	else
		pre->left = node;
	node->left = cur;
}

void	insert_redir(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	cur = tree->root;
	pre = cur;
	while (cur)
	{
		if (cur->type == TOKEN || cur->type == SQUOTE || cur->type == DQUOTE)
			break ;
		pre = cur;
		if (cur->type == PIPE)
			cur = cur->right;
		else
			cur = cur->left;
	}
	if (!pre || pre == cur)
		tree->root = node;
	else if (pre->type == PIPE)
		pre->right = node;
	else
		pre->left = node;
	node->left = cur;
}

void	insert_path(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

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
}

void	insert_filename(t_astree *tree, t_node *node)
{
	t_node	*cur;
	t_node	*pre;

	cur = tree->root;
	while (cur)
	{
		pre = cur;
		if (cur->type == PIPE)
			cur = cur->right;
		else if (cur->type == REDIR || cur->type == HEREDOC)
		{
			if (cur->right)
				cur = cur->left;
			else
				cur = cur->right;
		}
		else
			cur = cur->left;
	}
	if (pre->type == PIPE || !pre->right)
		pre->right = node;
	else
		pre->left = node;
}

void	insert_heredoc_redir(void)
{
	t_tok	*new_tok;
	t_node	*new_node;
	char	*itoa;

	new_tok = (t_tok *)malloc(sizeof(t_tok));
	if (!new_tok)
		print_strerr(errno);
	new_tok->type = REDIR;
	new_tok->data = ft_strdup("<");
	new_tok->next = 0;
	new_node = create_node(new_tok);
	insert_redir(get_info()->tree, new_node);
	new_tok->type = TOKEN;
	free(new_tok->data);
	itoa = ft_itoa(get_info()->h_count++);
	new_tok->data = ft_strjoin(".heredoc_", itoa);
	free(itoa);
	itoa = 0;
	insert_filename(get_info()->tree, create_node(new_tok));
	free(new_tok->data);
	new_tok->data = 0;
	free(new_tok);
	new_tok = 0;
}
