/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:49:35 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/17 14:55:09 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	heredoc(t_list *lst)
{
	char		*input;
	t_heredoc	*content;

	content = ((t_heredoc *)lst->content);
	while (get_info()->is_hdoc == TRUE)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[2C", STDOUT_FILENO);
			break ;
		}
		if (!ft_strcmp(input, content->eof))
		{
			free(input);
			break ;
		}
		ft_putendl_fd(input, content->fd);
		free(input);
	}
}

void	start_heredoc(t_node *hdoc_node)
{
	t_node	*eof;

	get_info()->is_hdoc = TRUE;
	eof = hdoc_node->right;
	ft_lstadd_back(&get_info()->hdoc_list, ft_lstnew(new_heredoc(eof)));
	heredoc(ft_lstlast(get_info()->hdoc_list));
	if (get_info()->is_hdoc == FALSE)
		return ;
	read_tree(hdoc_node->left);
}
