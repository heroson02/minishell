/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:50:30 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 21:23:13 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_atoi_(const char *str)
{
	char		*s;
	long long	ret;
	long long	flag;

	s = (char *)str;
	ret = 0;
	flag = 1;
	while (ft_isblank(*s))
		s++;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			flag = -1;
	while (ft_isdigit(*s))
	{
		ret = ret * 10 + *s - '0';
		s++;
	}
	while (ft_isblank(*s))
		s++;
	if (*s)
		return (-1);
	return (ret * flag);
}

void	builtin_exit(t_node *cmd)
{

	get_info()->exitcode = 0;
	ft_putendl_fd("exit", get_info()->file->origin_stdout);
	if (cmd->left)
	{
		get_info()->exitcode = ft_atoi_(cmd->left->data);
		if (get_info()->exitcode < 0)
		{
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(cmd->left->data, STDERR);
			ft_putendl_fd(": numeric argument required", STDERR);
			get_info()->exitcode += 256;
		}
		else if (cmd->left->left)
		{
			ft_putendl_fd("minishell: exit: too many arguments", STDERR);
			get_info()->exitcode = 1;
			return ;
		}
	}
	exit(get_info()->exitcode);
}
