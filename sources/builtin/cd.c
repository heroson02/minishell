/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:37:30 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/18 18:20:17 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*ft_cd(t_node *cmd)
{
	char	*path;
	char	*origin;
	char	*home;

	home = getenv("HOME");
	if (cmd->left && cmd->left->data[0] == '~')
	{
		origin = ft_substr(cmd->left->data, 1, ft_strlen(cmd->left->data) - 1);
		path = ft_strjoin(home, origin);
		free(origin);
		origin = 0;
		origin = cmd->left->data;
		free(origin);
		origin = 0;
		cmd->left->data = path;
	}
	return (home);
}

void	builtin_cd(t_node *cmd)
{
	char	*home;

	home = ft_cd(cmd);
	if (!cmd->left)
		chdir(home);
	else if (chdir(cmd->left->data) < 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR);
		if (cmd->left->data[0] == '-' && cmd->left->data[1])
		{
			ft_putchar_fd(cmd->left->data[0], STDERR);
			ft_putchar_fd(cmd->left->data[1], STDERR);
			ft_putendl_fd(": invalid option", STDERR);
			ft_putendl_fd("cd: usage: cd [dir]", STDERR);
		}
		else
		{
			ft_putstr_fd(cmd->left->data, STDERR);
			ft_putstr_fd(": ", STDERR);
			ft_putendl_fd(strerror(errno), STDERR);
		}
		get_info()->exitcode = 1;
		return ;
	}
	get_info()->exitcode = 0;
}
