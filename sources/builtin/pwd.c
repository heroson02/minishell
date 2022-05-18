/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:01:08 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/18 13:43:04 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(t_node *cmd)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * (BUFSIZ + 1));
	if (!pwd)
		print_strerr(errno);
	if (cmd->left && cmd->left->data[0] == '-' && cmd->left->data[1])
	{
		ft_putstr_fd("minishell: pwd: ", STDERR);
		ft_putchar_fd(cmd->left->data[0], STDERR);
		ft_putchar_fd(cmd->left->data[1], STDERR);
		ft_putendl_fd(": invalid option", STDERR);
		ft_putendl_fd("pwd: usage: pwd with no option", STDERR);
		get_info()->exitcode = 1;
	}
	else
	{
		getcwd(pwd, BUFSIZ);
		ft_putendl_fd(pwd, STDOUT);
		get_info()->exitcode = 0;
	}
	free(pwd);
	pwd = 0;
}
