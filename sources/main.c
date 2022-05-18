/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:40:18 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/18 12:51:29 by hyojlee          ###   ########.fr       */
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
	if (!(info->file))
		print_strerr(errno);
	ft_bzero(info->file, sizeof(t_file));
	env_preprocess(envp);
	get_org_term();
}

static void	ctrl_d(void)
{
	ft_putstr_fd("\033[1A", STDOUT);
	ft_putstr_fd("\033[11C", STDOUT);
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

static void	update_shlvl(void)
{
	t_node	cmd_node;
	t_node	new_node;
	char	*new_lvl;
	int		org_exitcode;

	ft_bzero(&cmd_node, sizeof(t_node));
	ft_bzero(&new_node, sizeof(t_node));
	cmd_node.data = "export";
	cmd_node.type = TOKEN;
	new_lvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	new_node.data = ft_strjoin("SHLVL=", new_lvl);
	new_node.type = TOKEN;
	cmd_node.left = &new_node;
	org_exitcode = get_info()->exitcode;
	builtin_export(&cmd_node);
	get_info()->exitcode = org_exitcode;
	free(new_lvl);
	free(new_node.data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	init(argc, argv, envp);
	while (1)
	{
		set_new_term();
		update_shlvl();
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
