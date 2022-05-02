/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:40:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/28 17:30:15 by hyojlee          ###   ########.fr       */
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

void	print_err(int err)
{
	if (err > 0)
		printf("\033[31m%s\033[0m\n", strerror(errno));
	else
		printf("\033[31mSyntax Error\033[0m\n");
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

void	astree_print(t_node *node);


int main(int argc, char **argv, char **envp)
{
	// char	**path;
	char	*line;
	t_info	info;
	
	(void)argc;
	(void)argv;
	// path = ft_split(get_env(envp, "PATH"), ':');
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	info.list = create_list();
	info.tree = create_tree();
	env_preprocess(&info, envp);
	// info.env = envp;
	while (1)
	{
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] == '\0')
				continue ;
			if (check_quote(line) == FALSE)	//따옴표 체크
				print_err(0); //syntax error 258
			tokenize(&(info.list), line);	// 토큰화
			// print_token(info.list);
			//구문 분석 및 파싱 과정 (AST TREE)
			if (syntax(&info) == FALSE)
				print_err(0); //syntax error 258
			if (chk_syntax(info.tree->root) == FALSE)
				print_err(0); //syntax error 258
			// print_tree(info.tree->root);
			// printf("\n\n");
			//환경변수 치환
			replace_recur(&info, info.tree->root);
			// print_tree(info.tree->root);
			//실행 과정 (이후에 tok list 비우기)
			read_tree(&info);
			ft_clear(&info);
			add_history(line);
			free(line);
			line = NULL;
			// system("leaks minishell");
		}
		else //ctrl + d
		{
			ft_putstr_fd("\x1b[1A", STDOUT);
			ft_putstr_fd("\033[12C", STDOUT);
			printf("exit\n");
			exit(0); //마지막 종료 상태 값 exit 인자로 넣기
		}
	}
	
	return (0);
}