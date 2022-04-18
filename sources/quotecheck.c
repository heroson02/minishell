/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotecheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 12:59:59 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/14 13:00:02 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	check_quote(char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			if (ft_strchr(str + 1, '\''))
				str = ft_strchr(str + 1, '\'');
			else
				return (FALSE);
		}
		else if (*str == '\"')
		{
			if (ft_strchr(str + 1, '\"'))
				str = ft_strchr(str + 1, '\"');
			else
				return (FALSE);
		}
		str++;
	}
	return (TRUE);
}
