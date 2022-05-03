/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:37:13 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/03 13:23:55 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	env = 0;
	free(str);
	str = 0;
	return (ret);
}

void	join_str(char **before, char *data, int *start, int end)
{
	char	*ret;
	char	*tmp;

	if (end - *start > 0)
		{
		tmp = ft_substr(data, *start, end - *start);
		ret = *before;
		*before = ft_strjoin(*before, tmp);
		free(tmp);
		tmp = 0;
		free(ret);
		ret = 0;
	}
	*start = end + 1;
}

void	replace_envp(t_info *info, char **before, char *data, int start, int end)
{
	char	*origin;
	char	*env;

	if (end - start < 1)
		return ;
	origin = ft_substr(data, start, end - start);
	env = replace_env(info, origin);
	// free(origin); //replace_env 안에서 free()해줌
	origin = *before;
	*before = ft_strjoin(*before, env);
	free(env);
	env = 0;
	free(origin);
	origin = 0;
}

char	*replace_token(t_info *info, char *data)
{
	char	*ret;
	int		dquote;
	int		front;
	int		end;

	dquote = FALSE;
	ret = ft_strdup("");
	end = 0;
	front = end;
	while (data[end])
	{
		if (data[end] == SQUOTE && dquote == FALSE)
		{
			join_str(&ret, data, &front, end);
			end = ft_strlen(data) - ft_strlen(ft_strchr(data + front, SQUOTE));
			join_str(&ret, data, &front, end);
		}
		else if (data[end] == DQUOTE && dquote == FALSE)
		{
			dquote = TRUE;
			join_str(&ret, data, &front, end);
		}
		else if (data[end] == DQUOTE && dquote == TRUE)
		{
			dquote = FALSE;
			join_str(&ret, data, &front, end);
		}
		else if (data[end] == '$')
		{
			join_str(&ret, data, &front, end++);
			while (data[end] && data[end] != '\'' && data[end] != '\"' && !ft_isblank(data[end]) &&
					data[end] != '$')
				end++;
			replace_envp(info, &ret, data, front, end);
			front = end--;
		}
		end++;
	}
	return (ret);
}

void	replace_recur(t_info *info, t_node *node)
{
	char	*tmp;

	if (!node)
		return ;
	if (ft_strchr(node->data, '$'))
	{
		tmp = node->data;
		node->data = replace_token(info, node->data);
		printf("\033[31m%s\033[0m\n", node->data);
		free(tmp);
		tmp = 0;
	}
	replace_recur(info, node->left);
	replace_recur(info, node->right);
}
