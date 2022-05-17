/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:22:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/17 16:46:00 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_cmd_path(char *cmd, int fd, int idx)
{
	char	*path;
	char	**paths;
	char	*temp;

	paths = ft_split(get_env("PATH"), ':');
	path = 0;
	while (paths[idx])
	{
		temp = ft_strjoin(paths[idx++], "/");
		path = ft_strjoin(temp, cmd);
		fd = open(path, O_RDONLY, 0644);
		free(temp);
		if (fd > 0)
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

/*
**	./ : PATH 외의 명령어, / : 루트 디렉토리에 있는 명령어, ~/ : 홈 디렉토리, 그 외에는 PATH에서 검색
*/
static void	get_path(char *cmd, char **path)
{
	if (!ft_memcmp("./", cmd, 2) || !ft_memcmp("/", cmd, 1))
		*path = ft_strdup(cmd);
	else if (!ft_memcmp("~/", cmd, 2))
	{
		replace_home_dir(&cmd);
		*path = ft_strdup(cmd);
	}
	else
		*path = get_cmd_path(cmd, 0, 0);
}

static char	**list_to_array(t_list *head)
{
	char	**result;
	t_list	*curr;
	char	*temp;
	int		i;

	i = 0;
	result = malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (!result)
		print_strerr(errno);
	curr = head;
	while (curr)
	{
		temp = ft_strjoin(((t_enode *)curr->content)->key, "=");
		result[i] = ft_strjoin(temp, ((t_enode *)curr->content)->value);
		free(temp);
		i++;
		curr = curr->next;
	}
	result[i] = 0;
	return (result);
}

static void	ft_execve(t_node *cmd)
{
	char	*path;
	char	**opt;

	get_path(cmd->data, &path);
	opt = get_cmd_opt(cmd);
	execve(path, opt, list_to_array(get_info()->env_list));
}

void	exec(t_node *node)
{
	pid_t	pid;
	int		status;
	char	*path;

	status = 0;
	get_path(node->data, &path);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(node->data, STDERR);
		ft_putendl_fd(": command not found", STDERR);
		get_info()->exitcode = 127;
		return ;
	}
	free(path);
	path = 0;
	pid = fork();
	if (pid < 0)
		print_strerr(errno);
	else if (pid == 0)
		ft_execve(node);
	waitpid(pid, &(get_info()->exitcode), 0);
	if (get_info()->exitcode > 255)
		get_info()->exitcode -= 255;
}
