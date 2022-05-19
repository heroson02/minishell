/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:36:37 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/19 15:42:45 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		get_info()->exitcode = 1;
		get_info()->is_hdoc = FALSE;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	exec_signal(int status)
{
	int	sig;

	echoctl_off();
	if (WIFEXITED(status))
		get_info()->exitcode = status / 256;
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGQUIT)
		{
			ft_putendl_fd("Quit: 3", STDIN);
			get_info()->exitcode = 131;
		}
		else if (sig == SIGINT)
		{
			ft_putchar_fd('\n', STDIN);
			get_info()->exitcode = 130;
		}
	}
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
