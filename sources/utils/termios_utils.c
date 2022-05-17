/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:20:02 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:05:54 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_org_term(void)
{
	t_info	*info;

	info = get_info();
	tcgetattr(STDIN, &(info->org_term));
}

void	set_org_term(void)
{
	t_info	*info;

	info = get_info();
	tcsetattr(STDIN, TCSANOW, &(info->org_term));
}

void	set_new_term(void)
{
	t_info	*info;

	info = get_info();
	tcgetattr(STDIN, &(info->new_term));
	info->new_term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN, TCSANOW, &(info->new_term));
}
