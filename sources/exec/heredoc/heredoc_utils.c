/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:39:23 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 13:51:38 by yson             ###   ########.fr       */
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
	set_new_term(TRUE);
	return (heredoc);
}

void	clear_heredoc(void *content)
{
	t_heredoc *target;

	target = content;
	close(target->fd);
	unlink(target->h_name);
	free(target->h_name);
	free(target->eof);
	ft_bzero(target, sizeof(t_heredoc));
}

// void	sig_heredoc_handler(int signo)
// {
// 	t_info	*info;

// 	info = get_info();
// 	if (signo == SIGINT)
// 	{
// 		clear_heredoc();
// 		exit(1);
// 	}
// }

// void	set_termcap(void)
// {
// 	char	*env;
// 	char	*cm;
// 	char	*ce;
	
// 	env = getenv("TERM");
// 	if (!env)
// 		env = "xterm";
// 	if (tgetent(NULL, env) < 1)
// 		return ;
// 	cm = tgetstr("cm", NULL);
// 	ce = tgetstr("ce", NULL);
// }
