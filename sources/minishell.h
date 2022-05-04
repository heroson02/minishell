/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:39:28 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 21:43:59 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <string.h>
# include <sys/errno.h>
# include <fcntl.h>
# include "./parsing/astree.h"
# include "./gnl/gnl.h"

# define REPLACE 1

typedef struct s_file
{
	int	open_stdin;
	int open_stdout;
	int origin_stdin;
	int origin_stdout;
}	t_file;

typedef struct s_info
{
	t_tok_list	*list;
	t_astree	*tree;
	t_list		*env_list;
	t_file		*file;
	int			exitcode;
}	t_info;

typedef struct s_enode
{
	char	*key;
	char	*value;
}	t_enode;

/*
** utils
**	- useful functions used everywhere
*/

/*
** clear_utils.c
*/
void	ft_clear(t_info *info);

/*
** free_utils.c
*/
void	free_split(char **split);
void	free_enode(void *node);

/*
** print_utils.c
*/
void	print_token(t_tok_list *list);
void	print_tree(t_node* root);
void	print_err(t_info *info, char *line, int err);

/*
** replace_utils.c
*/
void	join_str(char **before, char *data, int *start, int end);
void	join_envp(char **before, char *env, int *start, int *end);
void	find_end_pos(char *data, int *end);
char	*get_env_or_status(t_info *info, char *env);
void	replace_home_dir(char **cmd);

/*
** utils.c
*/
int		ft_strcmp(char *s1, char *s2);
int		ft_isblank(char c);
char	*get_env(t_info *info, char *name);

/*
**	parsing
**	- the function of parsing codes
*/

/*
** env_list.c
*/
t_enode	*new_enode(char *env);
void	env_preprocess(t_info *info, char **envp);

/*
** list.c
*/
t_tok_list	*create_list(void);
void		add_token(t_tok_list **list, t_tok *new_tok);
t_tok		*get_token(t_tok_list *list, int pos);

/*
** syntax.c
*/
void	pipeline(t_info *info, int *idx);
void	cmd(t_info *info, int *idx);
void	simple_cmd(t_info *info, int *idx);
void	redirs(t_info *info, int *idx);
void	redir(t_info *info, int *idx);
void	args(t_info *info, int *idx);
void	path(t_info *info, int *idx);
void	filename(t_info *info, int *idx);
int		syntax(t_info *info);

/*
** tokenize.c
*/
void	tokenize(t_tok_list **list, char *str);

/*
** semantic.c
*/
int		check_quote(char *str);
int		chk_syntax(t_node *node);

/*
**	replace_env.c
*/
void	replace_recur(t_info *info, t_node *node);

/*
**	list.c
*/
t_tok_list	*create_list(void);
void		add_token(t_tok_list **list, t_tok *new_tok);
t_tok		*get_token(t_tok_list *list, int pos);

/*
**	list.c
*/
t_enode		*new_enode(char *env);
void		env_preprocess(t_info *info, char **envp);

/*
**	astree.c
*/
t_node	*create_node(t_tok	*token);
t_astree	*create_tree(void);

/*
**	astree_insert.c
*/
void	insert_pipe_heredoc(t_astree *tree, t_node *node);
void	insert_redir(t_astree *tree, t_node *node);
void	insert_path(t_astree *tree, t_node *node);
void	insert_filename(t_astree *tree, t_node *node);


/*
**	exec
**	- executing commands from AST
*/

/*
** read_tree.c
*/
void	read_tree(t_info *info, t_node *node);

/*
** ft_execve.c
*/
void	exec(t_info *info, t_node *node);

/*
** get_cmd_opt.c
*/
char	**get_cmd_opt(t_node *node);

/*
** redir.c
*/
int		connect_redir(t_info *info);
int		disconnect_redir(t_info *info);
void	redirection(t_info *info, t_node *node);

/*
** heredoc.c
*/

/*
**	builtin
**	- builtin commands in minishell
*/
void	builtin_cd(t_info *info, t_node *cmd);
void	builtin_echo(t_info *info, t_node *cmd);
void	builtin_env(t_info *info);
void	builtin_exit(t_info *info, t_node *cmd);
void	builtin_export(t_info *info, t_node *cmd);
void	builtin_pwd(t_info *info, t_node *cmd);
void	builtin_unset(t_info *info, t_node *cmd);

#endif
