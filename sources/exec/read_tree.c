/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:41:29 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/10 14:27:55 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	chk_command(t_info *info, t_node *node)
{
	connect_redir(info);
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
	disconnect_redir(info);
}

static void	execute_code(t_info *info, t_node *node)
{
	if (!node)
		return ;
	// if (node->type == HEREDOC)
	// 	//heredoc 실행
	if (node->type == PIPE)
		exec_pipe(info, node);
	if (node->type == REDIR)
		redirection(info, node);
	if (node->type == TOKEN)
		chk_command(info, node);
}

void	read_tree(t_info *info, t_node *node)
{
	info->file->origin_stdin = dup(STDIN);
	info->file->origin_stdout = dup(STDOUT);
	if (info->file->origin_stdin < 0 || info->file->origin_stdout < 0)
		printf("dup error\n");
	if (!node)
		return ;
	execute_code(info, node);
}
