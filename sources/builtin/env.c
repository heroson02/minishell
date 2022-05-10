/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:45:16 by yson              #+#    #+#             */
/*   Updated: 2022/05/10 14:38:16 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(void)
{
	t_list	*curr;
	t_info	*info;

	info = get_info();
	curr = info->env_list;
	while (curr)
	{
		printf("%s=%s\n", ((t_enode *)curr->content)->key, ((t_enode *)curr->content)->value);
		curr = curr->next;
	}
}
