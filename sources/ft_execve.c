/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:22:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/01 23:45:23 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	free_split(char **split)
{
	while (*split)
	{
		free(*split);
		*split = 0;
		split++;
	}
	free(split);
	split = 0;
}

char	*get_cmd_path(t_info *info, char *cmd)
{
	char	*path;
	char	**paths;
	int		fd;
	int		idx;

	paths = ft_split(get_env(info, "PATH"), ':');
	fd = 0;
	idx = 0;
	path = 0;
	while (paths[idx])
	{
		path = ft_strjoin(paths[idx++], cmd);
		fd = open(path, O_CREAT | O_EXCL, 0644);
		if (fd > -1)
		{
			close(fd);
			break ;
		}
		free(path);
		path = 0;
	}
	free_split(paths);
	return (path);
}

int	num_of_opt(t_node *node)
{
	int	ret;
	t_node	*tmp;

	ret = 1;
	tmp = node->left;
	while (tmp)
	{
		ret++;
		tmp = tmp->left;
	}
	return (ret);
}

int	ft_execve(t_info *info, t_node *cmd, char **env)
{
	char	*path;
	char	**opt;
	int		num;
	int		idx;
	
	path = get_cmd_path(info, cmd->data);
	if (!path)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->data, 2);
		ft_putendl_fd(": command not found", 2);
		info->exitcode = 127;
	}
	num = num_of_opt(cmd);
	idx = 0;
	opt = (char **)malloc(sizeof(char *) * (num + 1));
	while (idx < num)
		opt[idx++] = ft_strdup(cmd->left->data);
	opt[idx] = 0;
	return (execve(path, opt, env));
}