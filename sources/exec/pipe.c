/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:35:22 by yson              #+#    #+#             */
/*   Updated: 2022/05/10 14:55:31 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

pid_t	pipe_input(t_info *info, int *fd, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT);
		close(fd[1]);
		read_tree(info, node);
		exit(0);
	}
	return (pid);
}

pid_t	pipe_output(t_info *info, int *fd, t_node *node)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		printf("error\n");
	else if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN);
		close(fd[0]);
		read_tree(info, node);
		exit(0);
	}
	return (pid);
}

int exec_pipe(t_info *info, t_node *node)
{
	int		pipe_fd[2];
	int		pid_left;
	int		pid_right;
	
	if (pipe(pipe_fd) == -1)
		printf("error\n");
	pid_left = pipe_input(info, pipe_fd, node->left);
	waitpid(pid_left, NULL, 0);
	close(pipe_fd[1]);
	pid_right = pipe_output(info, pipe_fd, node->right);
	close(pipe_fd[0]);
	waitpid(pid_right, NULL, 0);
	return (1);
}
