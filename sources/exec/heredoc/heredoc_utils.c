/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:39:23 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 12:30:19 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_heredoc	*init_heredoc(t_node *eof)
{
	t_heredoc	*heredoc;
	int			flags;
	t_info		*info;
	char		*h_idx;
	
	heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!heredoc)
		return (0);
	ft_bzero(heredoc, sizeof(t_heredoc));
	info = get_info();
	flags = O_CREAT | O_TRUNC | O_RDWR;
	h_idx = ft_itoa(info->h_idx++);

	info->heredoc->fd = open(".minishell_heredoc", flags, 0644);
	if (info->heredoc->fd < 0)
		return (0);
	info->heredoc->eof = ft_strdup(eof->data);
	set_new_term(TRUE);
	return (heredoc);
}

void	clear_heredoc(void)
{
	t_info	*info;

	info = get_info();
	if (info->heredoc->eof)
	{
		free(info->heredoc->eof);
		info->heredoc->eof = 0;
	}
	close(info->heredoc->fd);
	unlink(".minishell_heredoc");
	ft_bzero(info->heredoc, sizeof(t_heredoc));
}

void	sig_heredoc_handler(int signo)
{
	t_info	*info;

	info = get_info();
	if (signo == SIGINT)
	{
		clear_heredoc();
		exit(1);
	}
}

void	set_termcap(void)
{
	char	*env;
	char	*cm;
	char	*ce;
	
	env = getenv("TERM");
	if (!env)
		env = "xterm";
	if (tgetent(NULL, env) < 1)
		return ;
	cm = tgetstr("cm", NULL);
	ce = tgetstr("ce", NULL);
}
