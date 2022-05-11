/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:37:26 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/11 12:08:56 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_node(t_node	*node)
{
	if (!node)
		return;
	delete_node(node->left);
	delete_node(node->right);
	free(node->data);
	node->data = 0; //ft_bzero(node->data, sizeof(char));
	free(node);
	node = 0; //ft_bzero(node, sizeof(t_node));
}

static void	tree_clear(t_astree *tree)
{
	if (!tree)
		return;
	delete_node(tree->root);
	ft_bzero(tree, sizeof(t_astree));
}

static void	list_clear(t_tok_list *list)
{
	t_tok	*curr;
	t_tok	*next;

	if (!list || !(list->count))
		return ;
	curr = list->head;
	while (curr)
	{
		next = curr->next;
		free(curr->data);
		curr->data = NULL;
		free(curr);
		ft_bzero(curr, sizeof(t_tok));
		curr = next;
	}
	ft_bzero(list, sizeof(t_tok_list));
}

void	ft_clear(void)
{
	t_info	*info;

	info = get_info();
	list_clear(info->list);
	tree_clear(info->tree);
	free(info->heredoc->eof);
	ft_bzero(info->heredoc, sizeof(t_heredoc));	
}
