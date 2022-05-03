/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:50:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/03 18:38:06 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	connect_redir(t_info *info)
{
	if (info->file->open_stdin > 0)
	{
		if (dup2(info->file->open_stdin, STDIN) < 0)
			return (FALSE);
	}
	if (info->file->open_stdout > 0)
	{
		if (dup2(info->file->open_stdout, STDOUT) < 0)
			return (FALSE);
	}
	return (TRUE);
}

int	disconnect_redir(t_info *info)
{
	int status;

	status = 0;
	if (info->file->open_stdin > 0)
	{
		if (dup2(info->file->origin_stdin, STDIN) < 0)
			return (FALSE);
	}
	if (info->file->open_stdout > 0)
	{
		if (dup2(info->file->origin_stdout, STDOUT) < 0)
			return (FALSE);
	}
	return (TRUE);
}

static void	init_redir(t_info *info)
{
	if (info->file->open_stdout > 0)
		close(info->file->open_stdout);
	if (info->file->open_stdin > 0)
		close(info->file->open_stdin);
}

int	redirection(t_info *info, t_node *node)
{
	int		fd;
	char	*path;

	path = node->right->data;
	//기존에 redir을 통해 fd가 존재한다면 close 해주기
	init_redir(info);
	if (!ft_strcmp(node->data, ">"))
		info->file->open_stdout = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(node->data, ">>"))
		info->file->open_stdout = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(node->data, "<"))
		info->file->open_stdin = open(path, O_RDONLY, 0644);
	else if (!ft_strcmp(node->data, "<<"))
		// heredoc
	if (fd < 0)
		printf("minishell: %s: No such file or directory\n", path);
	read_tree(info, node->left);
}