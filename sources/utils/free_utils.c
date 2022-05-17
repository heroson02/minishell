/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:39:35 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:02:46 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_split(char **split)
{
	int	idx;

	idx = -1;
	while (split[++idx])
	{
		free(split[idx]);
		split[idx] = 0;
	}
	free(split);
	split = 0;
}

//환경변수를 이름과 값을 구분해서 t_enode 구조체에 저장
void	free_enode(void *node)
{
	t_enode	*enode;

	enode = (t_enode *)node;
	free(enode->key);
	enode->key = 0;
	free(enode->value);
	enode->value = 0;
	free(enode);
	enode = 0;
}
