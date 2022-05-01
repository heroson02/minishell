/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:41:29 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/01 16:11:58 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_check(t_info *info, t_node *node)
{
	if (!ft_memcmp(node->data, "cd", ft_strlen(node->data)))
		builtin_cd(info, node);
	else if (!ft_memcmp(node->data, "echo", ft_strlen(node->data)))
		builtin_echo(info, node);
	else if (!ft_memcmp(node->data, "env", ft_strlen(node->data)))
		builtin_env(info);
	else if (!ft_memcmp(node->data, "exit", ft_strlen(node->data)))
		builtin_exit(info, node);
	else if (!ft_memcmp(node->data, "export", ft_strlen(node->data)))
		builtin_export(info, node);
	else if (!ft_memcmp(node->data, "pwd", ft_strlen(node->data)))
		builtin_pwd(info, node);
	else if (!ft_memcmp(node->data, "unset", ft_strlen(node->data)))
		builtin_unset(info, node);
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
