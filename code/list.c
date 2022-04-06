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

t_list *create_list(void)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (list == 0)
		return (0);
	ft_bzero(list, sizeof(t_list));
	return (list);
}

t_node *create_node(t_data data)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == 0)
		return (0);
	ft_bzero(node, sizeof(t_node));
	node->data = data;
	return (node);
}

void	add_token(t_list *list, t_data data)
{
	t_node *node;

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
