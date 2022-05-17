/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:35:39 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/17 16:47:17 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_enode	*new_enode(char *env)
{
	t_enode	*result;
	char	*value;

	result = (t_enode *)malloc(sizeof(t_enode));
	if (!result)
		print_strerr(errno);
	value = ft_strchr(env, '=');
	result->key = ft_substr(env, 0, ft_strlen(env) - ft_strlen(value));
	result->value = ft_substr(value, 1, ft_strlen(value) - 1);
	return (result);
}

void	env_preprocess(char **envp)
{
	t_list	*head;
	int		i;
	t_info	*info;

	info = get_info();
	i = 1;
	head = ft_lstnew(new_enode(envp[0]));
	info->env_list = head;
	while (envp[i])
	{
		ft_lstadd_back(&head, ft_lstnew(new_enode(envp[i])));
		i++;
	}
}
