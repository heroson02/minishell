/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:48:44 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/06 17:48:47 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

t_tok_list *create_list(void)
{
	t_tok_list	*list;

	list = (t_tok_list *)malloc(sizeof(t_tok_list));
	if (list == 0)
		return (0);
	ft_bzero(list, sizeof(t_tok_list));
	return (list);
}

t_tok *create_node(t_data data, t_type type)
{
	t_tok *node;

	node = (t_tok *)malloc(sizeof(t_tok));
	if (node == 0)
		return (0);
	ft_bzero(node, sizeof(t_tok));
	node->data = data;
	node->type = type;
	return (node);
}

void	add_token(t_tok_list *list, t_data data)
{
	t_tok *node;

	node = create_node(data);
	if (list->count == 0)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		node->prev = list->tail;
		list->tail->next = node;
		list->tail = node;
	}
}
