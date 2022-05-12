/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:40:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 11:33:06 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"


// static void	init(t_info *info)
// {
// 	ft_bzero(info, sizeof(t_info));
// 	info->list = create_list();
// 	info->tree = create_tree();
// 	info->file = (t_file *)malloc(sizeof(t_file));
// 	ft_bzero(info->file, sizeof(t_file));
// 	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
// 	ft_bzero(info->heredoc, sizeof(t_heredoc));
// 	get_org_term(info);
// }

static void	init(void)
{
	t_info	*info;

	info = get_info();
	ft_bzero(info, sizeof(t_info));
	info->heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	ft_bzero(info->heredoc, sizeof(t_heredoc));
	info->list = create_list();
	info->tree = create_tree();
	info->file = (t_file *)malloc(sizeof(t_file));
	ft_bzero(info->file, sizeof(t_file));
	get_org_term();
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	
	(void)argc;
	(void)argv;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	init();
	env_preprocess(envp);
	while (1)
	{
		line = readline("minishell> ");
		set_new_term(FALSE);
		if (line)
		{
			if (line[0] == '\0')
				continue ;
			add_history(line);
			if (check_quote(line) == FALSE)	//따옴표 체크
			{
				print_err(line, 0); //syntax error 258
				continue ; // 다시 명령줄 출력해야하므로
			}
			tokenize(&(get_info()->list), line);	// 토큰화
			print_token(get_info()->list);
			//구문 분석 및 파싱 과정 (AST TREE)
			if (syntax() == FALSE)
			{
				print_err(line, 0); //syntax error 258
				continue ;
			}
			print_tree(get_info()->tree->root);
			if (chk_syntax(get_info()->tree->root) == FALSE)
			{
				print_err(line, 0); //syntax error 258
				continue ;
			}
			// print_tree(get_info()->tree->root);
			// printf("\n\n");
			//환경변수 치환
			replace_recur(get_info()->tree->root);
			//실행 과정 (이후에 tok list 비우기)
			read_tree(get_info()->tree->root);
			ft_clear();
			// add_history(line); 위치 변경 73번째로 - 77번째때문에 add_history()가 안됨
			free(line);
			line = NULL;
			// system("leaks minishell");
			set_org_term();
		}
		else //ctrl + d
		{
			ft_putstr_fd("\x1b[1A", STDOUT);
			ft_putstr_fd("\033[12C", STDOUT);
			printf("exit\n");
			set_org_term();
			exit(0); //마지막 종료 상태 값 exit 인자로 넣기
		}
	}
	
	return (0);
}
