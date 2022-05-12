/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_yson.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:49:35 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 21:22:05 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

void	heredoc(t_list *lst)
{
	char		*input;
	// char		*result;
	t_heredoc	*content;

	content = ((t_heredoc *)lst->content);
	while (get_info()->exitcode != 130)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("\x1b[1A", STDOUT_FILENO);
			ft_putstr_fd("\033[2C", STDOUT_FILENO);
			break ;	
		}
		if (!ft_strcmp(input, content->eof))
			break ;
		ft_putendl_fd(input, content->fd);
		// result = ft_strjoin_free(result, input);
		// result = ft_strjoin_free(result, "\n");
		free(input);
	}
	// ft_putstr_fd(result, content->fd);
	// free(result);
}

void	start_heredoc_yson(t_node *hdoc_node)
{
	// pid_t	pid;
	t_node	*eof;

	get_info()->exitcode = 0;
	eof = hdoc_node->right;
	ft_lstadd_back(&get_info()->hdoc_list, ft_lstnew(new_heredoc(eof)));
	heredoc(ft_lstlast(get_info()->hdoc_list));
	if (get_info()->exitcode == 130)
		return ;
	// pid = fork();
	// signal(SIGINT, SIG_IGN);
	// if (pid < 0)
	// 	printf("fork error\n");
	// else if (pid == 0) //child process
	// 	child_routine();
	// waitpid(pid, &(get_info()->exitcode), 0);
	// signal(SIGINT, handler);
	read_tree(hdoc_node->left);
}

