/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:49:35 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 14:09:54 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	child_routine(void)
{
	// signal(SIGINT, sig_heredoc_handler);
	set_org_term();
}

void	start_heredoc(t_node *node)
{
	// pid_t	pid;
	t_node	*eof;

	eof = node->right;
	ft_lstadd_back(&get_info()->hdoc_list, ft_lstnew(new_heredoc(eof)));
	// pid = fork();
	// signal(SIGINT, SIG_IGN);
	// if (pid < 0)
	// 	printf("fork error\n");
	// else if (pid == 0) //child process
	// 	child_routine();
	// waitpid(pid, &(get_info()->exitcode), 0);
	read_tree(node->left);
}