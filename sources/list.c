/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:48:44 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/14 19:51:35 by yson             ###   ########.fr       */
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

static t_tok	*ft_toklast(t_tok *tok)
{
	while (tok)
	{
		if (!(tok->next))
			break ;
		tok = tok->next;
	}
	return (tok);
}

void	add_token(t_tok_list **list, t_tok *new_tok)
{
	t_tok	*last;

	if (!list || !new_tok)
		return ;
	if (!(*list)->head && (*list)->count == 0)
		(*list)->head = new_tok;
	else
	{
		last = ft_toklast((*list)->head);
		last->next = new_tok;
	}
	(*list)->count++;
}

t_tok	*get_token(t_tok_list *list, int pos)
{
	t_tok	*token;
	int		idx;

	idx = -1;
	if (!list || pos >= list->count)
		return (NULL);
	token = list->head;
	while (++idx < pos)
		token = token->next;
	return (token);
}
