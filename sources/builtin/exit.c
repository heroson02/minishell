/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 14:50:30 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:05:55 by hyojlee          ###   ########.fr       */
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
	t_info	*info;

	info = get_info();
	info->exitcode = 0;
	printf("exit\n");
	if (cmd->left)
	{
		info->exitcode = ft_atoi_(cmd->left->data);
		if (info->exitcode < 0)
		{
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(cmd->left->data, STDERR);
			ft_putendl_fd(": numeric argument required", STDERR);
			info->exitcode = 256 + info->exitcode;
		}
	}
	exit(info->exitcode);
}
