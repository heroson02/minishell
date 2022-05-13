/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:01:08 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:05:55 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(t_node *cmd)
{
	char	*pwd;

	pwd = (char *)malloc(sizeof(char) * (BUFSIZ + 1));
	if (!pwd)
		return ;
	if (cmd->left && cmd->left->data[0] == '-')
	{
		ft_putstr_fd("minishell: pwd: ", STDERR);
		ft_putstr_fd(cmd->left->data, STDERR);
		ft_putendl_fd(": invalid option", STDERR);
		ft_putendl_fd("pwd: usage: pwd with no option", STDERR);
		get_info()->exitcode = 1;
	}
	else
	{
		getcwd(pwd, BUFSIZ);
		printf("%s\n", pwd);
	}
	free(pwd);
	pwd = 0;
	get_info()->exitcode = 0;
}
