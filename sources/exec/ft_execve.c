/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:22:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/19 18:13:10 by hyojlee          ###   ########.fr       */
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
**	./ : Commands other than PATH,
**	/ : Commands in the root directory
**	~/ : Home directory, Otherwise search in PATH
*/
static void	get_path(t_node *data, char **path)
{
	char	*cmd;

	cmd = data->data;
	if (!ft_memcmp("./", cmd, 2) || !ft_memcmp("/", cmd, 1))
		*path = ft_strdup(cmd);
	else if (!ft_memcmp("~/", cmd, 2))
	{
		replace_home(data);
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
	result = (char **)malloc(sizeof(char *) * (ft_lstsize(head) + 1));
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

static void	ft_execve(t_node *cmd, char **env)
{
	char	*path;
	char	**opt;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	opt = get_cmd_opt(cmd);
	get_path(cmd, &path);
	echoctl_on();
	if (execve(path, opt, env) < 0)
	{
		ft_putstr_fd("minishell: ", STDERR);
		ft_putstr_fd(cmd->data, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putendl_fd(strerror(errno), STDERR);
		exit(127);
	}
}

void	exec(t_node *node, int status)
{
	pid_t	pid;
	char	*path;
	char	**env;

	get_path(node, &path);
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
	signal(SIGINT, SIG_IGN);
	env = list_to_array(get_info()->env_list);
	pid = fork();
	if (pid < 0)
		print_strerr(errno);
	else if (pid == 0)
		ft_execve(node, env);
	waitpid(pid, &(status), 0);
	exec_signal(status);
	free_split(env);
}
