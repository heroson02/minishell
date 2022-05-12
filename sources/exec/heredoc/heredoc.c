/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:49:35 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 21:18:42 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_heredoc	*get_eof(void)
{
	t_list	*cur;

	cur = get_info()->hdoc_list;
	while (cur->next)
		cur = cur->next;
	return (((t_heredoc	*)cur->content));
}

void	child_routine(void)
{
	char	*line;
	char	*tmp;
	char	*data;
	t_heredoc	*cur;
	
	signal(SIGINT, sig_heredoc_handler);
	cur = get_eof();
	data = ft_strdup("");
	while (1)
	{
		line = readline("> ");
		if (line && ft_strcmp(line, cur->eof))
		{
			tmp = line;
			line = ft_strjoin(line, "\n");
			free(tmp);
			tmp = data;
			data = ft_strjoin(data, line);
			free(tmp);
			free(line);
			line = 0;
		}
		else
		{
			if (ft_strcmp(line, cur->eof))
			{
				ft_putstr_fd("\033[1A", STDOUT);
				ft_putstr_fd("\033[2C", STDOUT);
			}
			break ;
		}
	}
	ft_putstr_fd(data, cur->fd);
	close(cur->fd);
	free(data);
	data = 0;
	// set_org_term();
}

void	start_heredoc(t_node *hdoc_node)
{
	pid_t	pid;
	t_node	*eof;

	eof = hdoc_node->right;
	ft_lstadd_back(&get_info()->hdoc_list, ft_lstnew(new_heredoc(eof)));
	pid = fork();
	signal(SIGINT, SIG_IGN);
	if (pid < 0)
		printf("fork error\n");
	else if (pid == 0) //child process
		child_routine();
	waitpid(pid, &(get_info()->exitcode), 0);
	signal(SIGINT, handler);
	printf("\033[36mexitcode: %d\033[0m\n", get_info()->exitcode);
	if (get_info()->exitcode != 256)
		read_tree(hdoc_node->left);
	else
	{
		// 처음 readline으로 돌아가야함.
		// 더이상 트리 순회하지 않아야함.
		read_tree(NULL);
		ft_clear();
	}
}