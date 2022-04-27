/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:37:13 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/27 20:43:31 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

// 환경변수 가져오는 함수 수정본
// 환경변수($HOME와 같은 애들) 값을 치환하기 위해 만들어둔 함수
// 환경변수가 존재하지 않으면 그냥 빈 문자열을 출력하므로 (echo $HELLO)
// name에 해당하는 환경변수가 존재하지 않으면 빈 문자열을 출력한다.
char	*get_env(char **env, char *name)
{
	char	*env_name;
	size_t	len;

	env_name = ft_strjoin(name, "=");
	len = ft_strlen(env_name);
	while (*env)
	{
		if (ft_strnstr(*env, env_name, ft_strlen(*env)))
		{
			free(env_name);
			env_name = 0;
			return (*env + len);
		}
		env++;
	}
	free(env_name);
	env_name = 0;
	return (ft_strdup(""));
	// if (!*env) //환경변수가 존재하지 않는다.
	// 	print_err(errno, 1);
	// return (0);
}

static void	free_split(char **split)
{
	int	idx;

	idx = -1;
	while (split[++idx])
	{
		free(split[idx]);
		split[idx] = 0;
	}
	free(split);
	split = 0;
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
	rpl = get_env(info->env, env);
	if (!str[idx])
		ret = ft_strdup(rpl);
	else
		ret = ft_strjoin(rpl, str + idx);
	free(env);
	env = 0;
	// free(rpl);
	// rpl = 0;
	free(str);
	str = 0;
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
	free(data);
	data = 0;
	idx = -1;
	while (split[++idx])
	{
		split[idx] = replace_env(info, split[idx]);
		data = newstr;
		newstr = ft_strjoin(newstr, split[idx]);
		free(data);
		data = 0;
	}
	free_split(split);
	node->data = newstr;
}

void	replace_recur(t_info *info, t_node *node)
{
	if (!node)
		return ;
	replace(info, node);
	replace_recur(info, node->left);
	replace_recur(info, node->right);
}
