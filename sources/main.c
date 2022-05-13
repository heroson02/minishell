/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:40:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 20:11:32 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static void	init(int argc, char **argv, char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = get_info();
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	ft_bzero(info, sizeof(t_info));
	info->list = create_list();
	info->tree = create_tree();
	info->file = (t_file *)malloc(sizeof(t_file));
	ft_bzero(info->file, sizeof(t_file));
	env_preprocess(envp);
	get_org_term();
}

static void	ctrl_d(void)
{
	ft_putstr_fd("\033[1A", STDOUT);
	ft_putstr_fd("\033[12C", STDOUT);
	ft_putendl_fd("exit", STDOUT);
	set_org_term();
	exit(get_info()->exitcode);
}

static int	chk_continue(char *line)
{
	add_history(line);
	if (check_quote(line) == FALSE)
	{
		print_err(line);
		return (TRUE);
	}
	tokenize(&(get_info()->list), line);
	if (syntax() == FALSE || chk_syntax(get_info()->tree->root) == FALSE)
	{
		print_err(line);
		return (TRUE);
	}
	return (FALSE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init(argc, argv, envp);
	while (1)
	{
		set_new_term();
		line = readline("minishell> ");
		if (line)
		{
			if (line[0] == '\0' || chk_continue(line) == TRUE)
				continue ;
			replace_recur(get_info()->tree->root);
			read_tree(get_info()->tree->root);
			ft_clear();
			free(line);
			line = NULL;
			// system("leaks minishell");
			set_org_term();
		}
		else
			ctrl_d();
	}
	return (0);
}
