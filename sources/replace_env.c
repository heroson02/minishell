/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:37:13 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/02 19:19:19 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	free_split(char **split)
{
	int	idx;

	idx = -1;
	while (split[++idx])
	{
		free(split[idx]);
		split[idx] = 0; //ft_bzero(split[idx], sizeof(char));
	}
	free(split);
	split = 0; //ft_bzero(split, sizeof(char *));
}

/*
** split('$')의 결과임
** split 호출 전에 strchr('$')을 하기 때문에 무조건 환경변수이름으로 시작하는 문자열(str)이 들어옴
** get_env한 결과(rpl에 들어가는 값)는 항상 동적할당되어있다. 빈 문자열인 경우 ""을 strdup해주기 때문.
*/
char	*replace_env(t_info *info, char *str)
{
	int		idx;
	char	*env;
	char	*rpl;
	char	*ret;

	idx = 0;
	while (str[idx] && !ft_isblank(str[idx]))
		idx++;
	env = ft_substr(str, 0, idx);
	rpl = get_env(info, env);
	if (!str[idx])
		ret = ft_strdup(rpl);
	else
		ret = ft_strjoin(rpl, str + idx);
	free(env);
	env = 0; // ft_bzero(env, sizeof(char));
	// free(rpl);
	// rpl = 0;
	free(str);
	str = 0; // ft_bzero(str, sizeof(char));
	return (ret);
}

void	replace(t_info *info, t_node *node)
{
	char	*newstr;
	char	*data;
	char	**split;
	int		idx;

	data = ft_strchr(node->data, '$');
	if (!data)
		return ;
	newstr = ft_substr(node->data, 0, ft_strlen(node->data) - ft_strlen(data));
	split = ft_split(data, '$');
	idx = -1;
	free(node->data);
	node->data = 0; // ft_bzero(node->data, sizeof(char));
	while (split[++idx])
	{
		split[idx] = replace_env(info, split[idx]);
		data = newstr;
		newstr = ft_strjoin(newstr, split[idx]);
		free(data);
		data = 0; // ft_bzero(data, sizeof(char));
	}
	free_split(split);
	node->data = newstr;
}

void	replace_recur(t_info *info, t_node *node)
{
	char	*tmp;

	if (!node)
		return ;
	if (node->type == SQUOTE || node->type == DQUOTE)
	{
		tmp = node->data;
		node->data = ft_substr(node->data, 1, ft_strlen(tmp) - 2);
		free(tmp);
		tmp = 0; // ft_bzero(tmp, sizeof(char));
	}
	if (node->type == DQUOTE || node->type == TOKEN)
		replace(info, node);
	replace_recur(info, node->left);
	replace_recur(info, node->right);
}
