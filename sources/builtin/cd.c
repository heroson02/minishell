/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:37:30 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/10 14:37:03 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_cd(t_node *cmd)
{
	char	*path;
	char	*origin;
	char	*home;
	t_info	*info;

	info = get_info();
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
	if (!cmd->left)
		chdir(home);
	else if (chdir(cmd->left->data) < 0)
	{
		ft_putstr_fd("bash: cd: ", STDERR);
		ft_putstr_fd(cmd->left->data, STDERR);
		if (cmd->left->data[0] == '-')
		{
			ft_putendl_fd(": invalid option", STDERR);
			ft_putendl_fd("cd: usage: cd [dir]", STDERR);
		}
		else
			ft_putendl_fd(": No such file or directory", STDERR);
		info->exitcode = 1;
	}
}