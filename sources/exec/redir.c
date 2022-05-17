/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:50:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:05:55 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	init_redir(int is_stdin)
{
	t_info	*info;

	info = get_info();
	if (is_stdin == FALSE && info->file->open_stdout > 0)
	{
		close(info->file->open_stdout);
		info->file->open_stdout = 0;
	}
	if (is_stdin == TRUE && info->file->open_stdin > 0)
	{
		close(info->file->open_stdin);
		info->file->open_stdin = 0;
	}
}

int	connect_redir(void)
{
	t_info	*info;

	info = get_info();
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

int	disconnect_redir(void)
{
	int		status;
	t_info	*info;

	info = get_info();
	status = 0;
	if (info->file->open_stdin > 0)
	{
		close(info->file->open_stdin);
		if (dup2(info->file->origin_stdin, STDIN) < 0)
			return (FALSE);
	}
	if (info->file->open_stdout > 0)
	{
		close(info->file->open_stdout);
		if (dup2(info->file->origin_stdout, STDOUT) < 0)
			return (FALSE);
	}
	return (TRUE);
}

void	redirection(t_node *node)
{
	char	*path;
	int		is_stdin;
	t_file	**file;

	file = &(get_info()->file);
	path = node->right->data;
	is_stdin = TRUE;
	if (node->data[0] == '>')
		is_stdin = FALSE;
	init_redir(is_stdin);
	if (!ft_strcmp(node->data, ">"))
		(*file)->open_stdout = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(node->data, ">>"))
		(*file)->open_stdout = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(node->data, "<"))
		(*file)->open_stdin = open(path, O_RDONLY, 0644);
	else if (!ft_strcmp(node->data, "<<"))
		printf("heredoc\n");
	if ((*file)->open_stdout < 0 || (*file)->open_stdin < 0)
	{
		printf("\033[34mminishell: %s: %s\033[0m\n", path, strerror(errno));
		return ;
	}
	read_tree(node->left);
}
