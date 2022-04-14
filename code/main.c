/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:40:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/06 15:40:20 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void handler(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}	
}

void	print_err(char *str, int exit_status)
{
	printf("%s\n", str);
	exit(exit_status);
}

// 환경변수 값 가져오는 함수 원본
// static char	*get_env_path(char **env)
// {
// 	while (*env)
// 	{
// 		if (ft_strnstr(*env, "PATH=/", ft_strlen(*env)))
// 			return (*env + 5);
// 		env++;
// 	}
// 	if (!*env)
// 		print_err("PATH", 1);
// 	return (0);
// }

// 환경변수 가져오는 함수 수정본
static char	*get_env_path(char **env, char *name)
{
	while (*env)
	{
		if (ft_strnstr(*env, name, ft_strlen(*env)))
			return (*env + ft_strlen(name));
		env++;
	}
	if (!*env)
		print_err(name, 1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char	**path;
	char	*line;
	t_tok_list	*list;

	path = ft_split(get_env_path(envp, "PATH="), ':');
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	list = create_list();
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (check_quote(line) == FALSE)	//따옴표 체크
				print_err("Syntax error", 258);
			tokenize(&list, line);	// 토큰화
			//어휘 분석 및 파싱 과정 (AST TREE)
			//실행 과정
			add_history(line);
			free(line);
			line = NULL;
		}
		else //ctrl + d
		{
			printf("exit\n");
			exit(0); //마지막 종료 상태 값 exit 인자로 넣기
		}
	}
	
	return (0);
}