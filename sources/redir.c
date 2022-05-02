/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 14:50:14 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/02 21:36:09 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// void	set_fdtable(t_file *file)
// {
// 	int	res;

// 	if (!file->in_out)
// 		res = dup2(file->fd, STDIN);
// 	else
// 		res = dup2(file->fd, STDOUT);
// 	if (res < 0) // 파일 디스크립터 복사 실패
// 		return ;
// }

// static t_file	*return_file(t_node *redir, t_file *file)
// {
// 	if (file->fd < 0)
// 	{
// 		free(file);
// 		file = 0;
// 	}
// 	set_fdtable(file);
// 	redir->file = file;
// 	return (file);
// }

// t_file	*new_file(t_node *redir)
// {
// 	t_file	*file;
// 	int		flags;

// 	if (!redir->right) // 밖에서 처리해주던지, 구문분석에서 잡아줄수도 있음.
// 		return (0);
// 	file = (t_file *)malloc(sizeof(t_file));
// 	if (!file)
// 		return (0);
// 	ft_bzero(file, sizeof(t_file));
// 	file->fd = open(redir->right->data, O_CREAT | O_EXCL, 0644); // 파일 존재 유무 확인
// 	if (file->fd < 0) // O_EXCL은 존재하면 실패
// 		file->exist = 1;
// 	else
// 		close(file->fd);
// 	flags = O_CREAT | O_RDONLY;
// 	if (redir->data[0] == '>')
// 	{
// 		file->in_out = 1;
// 		flags = O_CREAT | O_RDWR | O_APPEND;
// 		if (!(redir->data[1]))
// 			flags = O_CREAT | O_RDWR | O_TRUNC;
// 	}
// 	file->fd = open(redir->right->data, flags, 0644);
// 	return (return_file(redir, file));
// }

int	redirection(t_info *info, t_node *node)
{
	int		fd;
	char	*path;

	path = node->right->data;
	//기존에 redir을 통해 fd가 존재한다면 close 해주기
	if (!ft_strcmp(node->data, ">"))
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (!ft_strcmp(node->data, ">>"))
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (!ft_strcmp(node->data, "<"))
		fd = open(path, O_RDONLY, 0644);
	else if (!ft_strcmp(node->data, "<<"))
		// heredoc
	if (fd < 0)
		printf("minishell: %s: No such file or directory\n", path); exit(1);
	
}