/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:01:08 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/28 18:21:35 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(t_info *info, t_node *cmd)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * (BUFSIZ + 1));
	if (!pwd)
		return ;
	if (cmd->left && cmd->left->data[0] == '-')
	{
		ft_putstr_fd("bash: pwd: ", STDERR);
		ft_putstr_fd(cmd->left->data, STDERR);
		ft_putendl_fd(": invalid option", STDERR);
		ft_putendl_fd("pwd: usage: pwd with no option", STDERR);
		info->exitcode = 1;
	}
	else
	{
		getcwd(pwd, BUFSIZ);
		printf("%s\n", pwd);
	}
	free(pwd);
	pwd = 0;
}