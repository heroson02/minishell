/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:39:23 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/17 15:56:06 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_heredoc	*new_heredoc(t_node *eof)
{
	t_heredoc	*heredoc;
	int			flags;
	char		*h_idx;

	heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (0);
	ft_bzero(heredoc, sizeof(t_heredoc));
	h_idx = ft_itoa(get_info()->h_idx++);
	heredoc->h_name = ft_strjoin(".heredoc_", h_idx);
	free(h_idx);
	h_idx = 0;
	flags = O_CREAT | O_TRUNC | O_RDWR;
	heredoc->fd = open(heredoc->h_name, flags, 0644);
	if (heredoc->fd < 0)
	{
		free(heredoc->h_name);
		ft_bzero(heredoc, sizeof(t_heredoc));
		free(heredoc);
		return (0);
	}
	heredoc->eof = ft_strdup(eof->data);
	return (heredoc);
}

void	clear_heredoc(void *content)
{
	t_heredoc	*target;

	if (content)
	{
		target = (t_heredoc *)content;
		unlink(target->h_name);
		close(target->fd);
		free(target->h_name);
		free(target->eof);
		ft_bzero(target, sizeof(t_heredoc));
		free(target);
	}
}
