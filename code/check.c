/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:32:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/06 16:32:21 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	chk_quote(char *line)
{
	int i;
	int j;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			j = i;
			while (line[++j])
			{
				if (line[j] == ' ')
					line[j] = REPLACE;
				if (line[j] == line[i])
				{
					i = j;
					break ;
				}
			}
			if (line[j] == 0)
				return (FALSE);
		}
		i++;
	}
	return (TRUE);
}
