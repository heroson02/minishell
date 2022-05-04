/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 23:22:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 15:32:45 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*get_cmd_path(t_info *info, char *cmd, int fd, int idx)
{
	char	*path;
	char	**paths;
	char	*temp;

	paths = ft_split(get_env(info, "PATH"), ':');
	path = 0;
	while (paths[idx])
	{
		temp = ft_strjoin(paths[idx++], "/");
		path = ft_strjoin(temp, cmd);
		fd = open(path, O_RDONLY, 0644);
		if (fd > 0)
		{
			close(fd);
			break ;
		}
		free(temp);
		free(path);
		path = 0;
	}
	// printf("path : %s\n", path);
	free_split(paths);
	return (path);
}

void	replace_home_dir(char **cmd)
{
	char *home;
	char *result;
	char *target;

	target = *cmd;
	home = getenv("HOME");
	result = ft_strjoin(home, ++target);
	free(*cmd);
	*cmd = 0;
	*cmd = result;
}

/*
**	./ : PATH 외의 명령어, / : 루트 디렉토리에 있는 명령어, ~/ : 홈 디렉토리, 그 외에는 PATH에서 검색
*/
void	get_path(t_info *info, char *cmd, char **path)
{
	if (!ft_memcmp("./", cmd, 2) || !ft_memcmp("/", cmd, 2))
		*path = ft_strdup(cmd);
	else if (!ft_memcmp("~/", cmd, 2))
	{
		replace_home_dir(&cmd);
		*path = ft_strdup(cmd);
	}
	else
		*path = get_cmd_path(info, cmd, 0, 0);
}

char	**list_to_array(t_list *head)
{
	char	**result;
	t_list	*curr;
	char	*temp;
	int		i;
	
	i = 0;
	result = malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (!result)
		return (0);
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

int	ft_execve(t_info *info, t_node *cmd)
{
	char	*path;
	char	**opt;
	int		num;	//옵션을 만드는 코드를 함수화해서 빼야 할 듯

	get_path(info, cmd->data, &path);
	//path에서 검사한 명령어의 경우에는 걸리지만, 현재 디렉토리나 홈 디렉토리에서 찾을 때 에러는 검출이 안될 듯
	if (!path)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd->data, 2);
		ft_putendl_fd(": command not found", 2);
		info->exitcode = 127;
		return (info->exitcode);
	}
	opt = get_argv(cmd);
	// for (int i = 0; opt[i]; i++)
	// {
	// 	printf("opt[%d] : %s\n", i, opt[i]);
	// }
	
	num = execve(path, opt, list_to_array(info->env_list)); //exec의 결과값이 필요할까?
	free_split(opt);
	return (num);
}

void	exec(t_info *info, t_node *node)
{
	pid_t	pid;
	int		status;

	connect_redir(info);
	pid = fork();
	if (pid < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		status = ft_execve(info, node);
		exit(status);
	}
	waitpid(pid, 0, 0);
	info->exitcode = status;
	disconnect_redir(info);
	//pipe나 redir이 있을 경우에는 또 달라질 듯. 
}
