/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_home.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:37:13 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/03 14:42:28 by hyojlee          ###   ########.fr       */
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

void	join_str(char **before, char *start, char *end)
{
	char	*ret;
	char	*tmp;

	tmp = ft_substr(start, 0, ft_strlen(start) - ft_strlen(end));
	ret = *before;
	*before = ft_strjoin(*before, tmp);
	free(tmp);
	tmp = 0;
	free(ret);
	ret = 0;
}

void	replace_envp(t_info *info, char **before, char *start, char *end)
{
	char	*origin;
	char	*env;

	if (end)
		origin = ft_substr(start, 0, ft_strlen(start) - ft_strlen(end));
	else
		origin = ft_strdup(start);
	env = replace_env(info, ++origin);
	printf("\033[33m%s\033[0m\n", env);
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
	char	*cur;
	int		dquote;

	cur = data;
	dquote = FALSE;
	ret = ft_strdup("");
	while (*data)
	{
		if (*data == SQUOTE && dquote == FALSE)
		{
			cur = ++data;
			data = ft_strchr(data, SQUOTE);
			join_str(&ret, cur, data++);
			cur = data;
		}
		else if (*data == DQUOTE && dquote == TRUE)
		{
			dquote = FALSE;
			join_str(&ret, cur, data);
			cur = data;
		}
		else if (*data == DQUOTE && dquote == FALSE)
		{
			cur = data + 1;
			dquote = TRUE;
		}
		else if (*data == '$')
		{
			join_str(&ret, cur, data);
			cur = data++;
			while (*data && *data != '\"' && *data != '$' && !ft_isblank(*data) && *data != '\'')
				data++;
			replace_envp(info, &ret, cur, data);
			cur = data--;
		}
		data++;
	}
	return (ret);
}

// char	*replace_token(t_info *info, char *data)
// {
// 	char	*ret;
// 	char	*cur;
// 	int		dquote;
// 	int		squote;

// 	cur = data;
// 	dquote = FALSE;
// 	squote = FALSE;
// 	ret = ft_strdup("");
// 	while (*data)
// 	{
// 		if (*data == DQUOTE && dquote == FALSE && squote == FALSE)
// 		{
// 			cur++;
// 			dquote = TRUE;
// 		}
// 		else if (*data == SQUOTE && dquote == FALSE && squote == FALSE)
// 		{
// 			cur++;
// 			squote = TRUE;
// 		}
// 		else if (squote == FALSE && *data == '$')
// 		{
// 			join_str(&ret, cur, data);
// 			cur = data++;
// 			while (*data && *data != '\"' && *data != '$' && !ft_isblank(*data) && *data != '\'')
// 				data++;
// 			replace_envp(info, &ret, cur, data);
// 			cur = data;
// 		}
// 		else if (squote == FALSE && dquote == TRUE && *data == DQUOTE)
// 		{
// 			dquote = FALSE;
// 			join_str(&ret, cur, data);
// 			cur = data + 1;
// 		}
// 		else if (squote == TRUE && dquote == FALSE && *data == SQUOTE)
// 		{
// 			squote = FALSE;
// 			join_str(&ret, cur, data);
// 			cur = data + 1;
// 		}
// 		data++;
// 	}
// 	return (ret);
// }

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
	// if (node->type == SQUOTE || node->type == DQUOTE)
	// {
	// 	tmp = node->data;
	// 	node->data = ft_substr(node->data, 1, ft_strlen(tmp) - 2);
	// 	free(tmp);
	// 	tmp = 0; // ft_bzero(tmp, sizeof(char));
	// }
	// if (node->type == DQUOTE || node->type == TOKEN)
	// 	replace(info, node);
	replace_recur(info, node->left);
	replace_recur(info, node->right);
}
