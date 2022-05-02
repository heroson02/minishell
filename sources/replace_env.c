// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   replace_env.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/04/27 15:37:13 by hyojlee           #+#    #+#             */
// /*   Updated: 2022/05/02 16:58:45 by hyojlee          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "./minishell.h"

void	free_split(char **split)
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

void	replace(t_info *info, char **ndata)
{
	char	*newstr;
	char	*data;
	char	**split;
	int		idx;

	data = ft_strchr(*ndata, '$');
	if (!data)
		return ;
	newstr = ft_substr(*ndata, 0, ft_strlen(*ndata) - ft_strlen(data));
	split = ft_split(data, '$');
	idx = -1;
	free(*ndata);
	*ndata = 0; // ft_bzero(*ndata, sizeof(char));
	while (split[++idx])
	{
		split[idx] = replace_env(info, split[idx]);
		data = newstr;
		newstr = ft_strjoin(newstr, split[idx]);
		free(data);
		data = 0; // ft_bzero(data, sizeof(char));
	}
	free_split(split);
	*ndata = newstr;
}

char	*join_split(char **split)
{
	char	*join;
	char	*tmp;
	int		idx;

	idx = 0;
	join = ft_strdup("");
	while (split[idx])
	{
		tmp = join;
		join = ft_strjoin(join, split[idx++]);
		free(tmp);
		tmp = 0;
	}
	return (join);
}

void	separate_quote(t_info *info, t_node *node)
{
	char	*join;
	char	**split;
	int		idx;

	idx = 0;
	if (!ft_strchr(node->data, '\'') && !ft_strchr(node->data, '\"'))
	{
		replace(info, &(node->data));
		return ;
	}
	split = ft_split(node->data, '\'');
	join = join_split(split);
	free_split(split);
	split = ft_split(join, '\"');
	while (split[idx])
		replace(info, &(split[idx++]));
	free(node->data);
	free(join);
	join = join_split(split);
	node->data = ft_strdup(join);
	free(join);
	join = 0;
	free_split(split);
}

void	replace_recur(t_info *info, t_node *node)
{
	char	*tmp;

	if (!node)
		return ;
	separate_quote(info, node);
	replace_recur(info, node->left);
	replace_recur(info, node->right);
}