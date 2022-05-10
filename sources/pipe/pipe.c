/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:35:22 by yson              #+#    #+#             */
/*   Updated: 2022/05/10 11:52:17 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int exec_pipe(t_info *info, t_node *node)
{
	pid_t	pid;
	int		pipe_fd[2];

	pid = fork();
	if (pipe(pipe_fd))
		printf("pipe error\n");
	if (pid < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		
	}
	
}
