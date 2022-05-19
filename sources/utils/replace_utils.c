/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:37:13 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/19 17:21:46 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_home(t_node *data)
{
	char	*home;
	char	*org;
	char	*path;

	home = get_env("HOME");
	if (!home || !home[0])
		home = getenv("HOME");
	if (data && data->data[0] == '~')
	{
		org = ft_substr(data->data, 1, ft_strlen(data->data) - 1);
		path = ft_strjoin(home, org);
		free(org);
		org = data->data;
		free(org);
		org = 0;
		data->data = path;
	}
	return (home);
}

void	join_str(char **new_data, char *org_data, int *start, int end)
{
	char	*origin;
	char	*new_str;

	if (end - *start > 0)
	{
		new_str = ft_substr(org_data, *start, end - *start);
		origin = *new_data;
		*new_data = ft_strjoin(*new_data, new_str);
		free(new_str);
		new_str = 0;
		free(origin);
		origin = 0;
	}
	*start = end + 1;
}

void	join_envp(char **new_data, char *env, int *start, int *end)
{
	char	*origin;

	origin = *new_data;
	*new_data = ft_strjoin(*new_data, env);
	free(env);
	env = 0;
	free(origin);
	origin = 0;
	*start = *end;
	*end -= 1;
}

void	find_end_pos(char *data, int *end, int *is_replace)
{
	char	cur;
	int		new_end;

	new_end = *end;
	cur = data[new_end];
	*is_replace = TRUE;
	if ((new_end - 2 >= 0) && data[new_end - 2])
		*is_replace = FALSE;
	while (cur && cur != '\'' && cur != '\"' && !ft_isblank(cur)
		&& cur != '$' && cur != '=')
	{
		if (cur == '?')
		{
			new_end++;
			break ;
		}
		cur = data[(++new_end)];
	}
	*end = new_end;
}

char	*get_env_or_status(char *env)
{
	char	*ret;

	if (!ft_strcmp(env, "?"))
		ret = ft_itoa(get_info()->exitcode);
	else
		ret = ft_strdup(get_env(env));
	free(env);
	env = 0;
	return (ret);
}
