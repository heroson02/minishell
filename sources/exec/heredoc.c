/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:49:35 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/10 14:49:48 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_heredoc(t_info *info, t_node *eof)
{
	int		flags;
	
	flags = O_CREAT | O_TRUNC | O_RDWR;
	info->heredoc->fd = open(".minishell_heredoc", flags, 0644);
	if (info->heredoc->fd < 0)
		return ;
	info->heredoc->eof = ft_strdup(eof->data);
}

void	sig_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		exit(1);
	}
}

void	child_routine(t_info *info)
{

}

void	start_heredoc(t_node *eof)
{
	pid_t	pid;
	t_info	*info;

	info = get_info();
	init_heredoc(info, eof);
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid < 0)
		printf("fork error\n");
	else if (pid == 0) //child process
		child_routine(info);
}