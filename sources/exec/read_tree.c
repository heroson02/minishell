/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:41:29 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 17:01:06 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	chk_command(t_node *node)
{
	connect_redir();
	if (!ft_strcmp(node->data, "cd"))
		builtin_cd(node);
	else if (!ft_strcmp(node->data, "echo"))
		builtin_echo(node);
	else if (!ft_strcmp(node->data, "env"))
		builtin_env(node);
	else if (!ft_strcmp(node->data, "exit"))
		builtin_exit(node);
	else if (!ft_strcmp(node->data, "export"))
		builtin_export(node);
	else if (!ft_strcmp(node->data, "pwd"))
		builtin_pwd(node);
	else if (!ft_strcmp(node->data, "unset"))
		builtin_unset(node);
	else
		exec(node);
	disconnect_redir();
}

static void	execute_code(t_node *node)
{
	if (!node)
		return ;
	if (node->type == HEREDOC)
		start_heredoc(node);
	else if (node->type == PIPE)
		exec_pipe(node);
	else if (node->type == REDIR)
		redirection(node);
	else if (node->type == TOKEN)
		chk_command(node);
	get_info()->is_hdoc = FALSE;
}

void	read_tree(t_node *node)
{
	t_info *info;

	info = get_info();
	info->file->origin_stdin = dup(STDIN); //원래의 STDIN
	info->file->origin_stdout = dup(STDOUT); //원래의 STDOUT
	if (info->file->origin_stdin < 0 || info->file->origin_stdout < 0)
		printf("dup error\n");
	if (!node)
		return ;
	execute_code(node);
}
