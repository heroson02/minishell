/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:45:16 by yson              #+#    #+#             */
/*   Updated: 2022/04/28 17:31:24 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_info *info)
{
	t_list	*curr;

	curr = info->env_list;
	while (curr)
	{
		printf("%s=%s\n", ((t_enode *)curr->content)->key, ((t_enode *)curr->content)->value);
		curr = curr->next;
	}
}
