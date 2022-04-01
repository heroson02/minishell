/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 14:36:24 by hyojlee           #+#    #+#             */
/*   Updated: 2021/07/01 13:37:55 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*new;
	t_list	*lnext;

	if (!lst || !f)
		return (0);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (0);
	tmp = new;
	lst = lst->next;
	while (lst)
	{
		lnext = ft_lstnew(f(lst->content));
		if (!lnext)
		{
			ft_lstclear(&tmp, del);
			return (0);
		}
		new->next = lnext;
		new = lnext;
		lst = lst->next;
	}
	return (tmp);
}
