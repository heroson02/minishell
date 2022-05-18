/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:11:53 by yson              #+#    #+#             */
/*   Updated: 2022/05/18 13:32:27 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	export_error(char *data)
{
	ft_putstr_fd("minishell: export: \'", STDERR);
	ft_putstr_fd(data, STDERR);
	ft_putendl_fd("\': not a valid identifier", STDERR);
	get_info()->exitcode = 1;
}

static void	export_no_args(void)
{
	t_list	*lst;
	t_list	*head;

	lst = ft_lstdup(get_info()->env_list);
	head = lst;
	env_sort(&lst);
	while (lst)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(((t_enode *)lst->content)->key, STDOUT);
		ft_putstr_fd("=\"", STDOUT);
		ft_putstr_fd(((t_enode *)lst->content)->value, STDOUT);
		ft_putendl_fd("\"", STDOUT);
		lst = lst->next;
	}
	ft_lstclear(&head, free_enode);
}

static int	key_validation(char *key)
{
	int	i;

	i = 0;
	if (key[0] == '=' || ft_isdigit(key[0]))
		return (0);
	while (key[i] && key[i] != '=')
	{
		if (ft_isdigit(key[i]) || ft_isalpha(key[i]) || key[i] == '_')
			i++;
		else
			return (0);
	}
	return (1);
}

static void	ft_export(t_info *info, char *data, int *arg_check)
{
	t_enode	*node;
	t_list	*cur;

	if (!ft_strcmp(data, ""))
		return ;
	*arg_check = 1;
	if (!key_validation(data))
	{
		export_error(data);
		return ;
	}
	if (!ft_strchr(data, '='))
		return ;
	cur = info->env_list;
	node = new_enode(data);
	while (cur && ft_strcmp(node->key, ((t_enode *)cur->content)->key))
		cur = cur->next;
	if (!cur)
		ft_lstadd_back(&(info->env_list), ft_lstnew(node));
	else
	{
		free_enode(cur->content);
		cur->content = node;
	}
}

void	builtin_export(t_node *cmd)
{
	t_node	*node;
	int		arg_check;

	arg_check = 0;
	node = cmd->left;
	get_info()->exitcode = 0;
	if (node && node->data[0] == '-')
	{
		ft_putstr_fd("minishell: export: ", STDERR);
		ft_putchar_fd(node->data[0], STDERR);
		ft_putchar_fd(node->data[1], STDERR);
		ft_putendl_fd(": invalid option", STDERR);
		ft_putendl_fd("export : usage: export with no options", STDERR);
		get_info()->exitcode = 2;
		return ;
	}
	while (node)
	{
		ft_export(get_info(), node->data, &arg_check);
		node = node->left;
	}
	if (!arg_check)
		export_no_args();
	else
		return ;
}
