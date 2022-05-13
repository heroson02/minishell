/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:55:42 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 20:18:51 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_err(char *line)
{
	ft_clear();
	free(line);
	line = NULL;
	ft_putendl_fd("minishell: syntax error", STDERR);
	get_info()->exitcode = 258;
}
