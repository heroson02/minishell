/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 20:20:35 by yson              #+#    #+#             */
/*   Updated: 2022/05/17 21:20:27 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_enode	*ft_enode_dup(t_enode *node)
{
	t_enode	*new;

	new = (t_enode *)malloc(sizeof(t_enode));
	if (!new)
		print_strerr(errno);
	new->key = ft_strdup(node->key);
	new->value = ft_strdup(node->value);
	return (new);
}

static int	enode_compare(t_list *l1, t_list *l2)
{
	char	*s1;
	char	*s2;

	s1 = ((t_enode *)l1->content)->key;
	s2 = ((t_enode *)l2->content)->key;
	return (ft_strcmp(s1, s2));
}

t_list	*ft_lstdup(t_list *lst)
{
	t_list	*new;
	t_list	*curr;

	curr = lst;
	new = ft_lstnew(ft_enode_dup(curr->content));
	if (!new)
		print_strerr(errno);
	curr = curr->next;
	while (curr)
	{
		ft_lstadd_back(&new, ft_lstnew(ft_enode_dup(curr->content)));
		curr = curr->next;
	}
	return (new);
}

void	env_sort(t_list **lst)
{
	t_list	**l1;
	t_list	**l2;
	void	*temp;

	l1 = lst;
	while ((*l1)->next)
	{
		l2 = &(*l1)->next;
		while (*l2)
		{
			if (enode_compare(*l1, *l2) > 0)
			{
				temp = (*l1)->content;
				(*l1)->content = (*l2)->content;
				(*l2)->content = temp;
			}
			l2 = &(*l2)->next;
		}
		l1 = &(*l1)->next;
	}
}
