/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:20:02 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/10 14:23:22 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

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

void	set_new_term(int is_heredoc)
{
	t_info	*info;

	info = get_info();
	tcgetattr(STDIN, &(info->new_term));
	if (is_heredoc == FALSE)
		info->new_term.c_lflag &= ~ECHOCTL;
	else
	{
		info->new_term.c_lflag &= ~(ICANON | ECHO);
		info->new_term.c_cc[VMIN] = 1;
		info->new_term.c_cc[VTIME] = 0;
	}
	tcsetattr(STDIN, TCSANOW, &(info->new_term));
}