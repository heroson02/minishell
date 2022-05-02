/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:41:29 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/02 17:40:36 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_check(t_info *info, t_node *node)
{
	if (!ft_strcmp(node->data, "cd"))
		builtin_cd(info, node);
	else if (!ft_strcmp(node->data, "echo"))
		builtin_echo(info, node);
	else if (!ft_strcmp(node->data, "env"))
		builtin_env(info);
	else if (!ft_strcmp(node->data, "exit"))
		builtin_exit(info, node);
	else if (!ft_strcmp(node->data, "export"))
		builtin_export(info, node);
	else if (!ft_strcmp(node->data, "pwd"))
		builtin_pwd(info, node);
	else if (!ft_strcmp(node->data, "unset"))
		builtin_unset(info, node);
	else
		exec(info, node);
}

void	execute_code(t_info *info, t_node *node)
{
	if (!node)
		return ;
	// if (node->type == HEREDOC)
	// 	//heredoc 실행
	// if (node->type == PIPE)
	// 	//pipe
	if (node->type == REDIR)
	{
		dup2(STDIN, info->stdin_fd);
		dup2(STDOUT, info->stdout_fd);
		new_file(node);
		if (!node->file->in_out)
			dup2(node->file->fd, info->stdin_fd);
		else
			dup2(node->file->fd, info->stdout_fd);
	}
	if (node->type == TOKEN)
		command_check(info, node);
	execute_code(info, node->left);
}

void	read_tree(t_info *info)
{
	t_node *node;

	node = info->tree->root;
	if (!node)
		return ;
	execute_code(info, node);
// 	node = node->left;
// 	node = node->right;
}
