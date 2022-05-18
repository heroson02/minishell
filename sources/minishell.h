/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:39:28 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/18 12:42:18 by hyojlee          ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include "./parsing/astree.h"
# include "../libft/libft.h"

# define REPLACE 1

typedef struct s_file
{
	int	open_stdin;
	int	open_stdout;
	int	origin_stdin;
	int	origin_stdout;
}	t_file;

typedef struct s_heredoc
{
	int					fd;
	char				*h_name;
	char				*eof;
}	t_heredoc;

typedef struct s_info
{
	t_tok_list		*list;
	t_astree		*tree;
	t_list			*env_list;
	t_file			*file;
	int				exitcode;
	struct termios	org_term;
	struct termios	new_term;
	int				is_hdoc;
	int				h_count;
	int				h_idx;
	int				is_pipe;
	t_list			*hdoc_list;
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
void		ft_clear(void);

/*
** free_utils.c
*/
void		free_split(char **split);
void		free_enode(void *node);

/*
** print_utils.c
*/
void		print_err(char *line);
void		print_strerr(int err);

/*
** replace_utils.c
*/
void		join_str(char **before, char *data, int *start, int end);
void		join_envp(char **before, char *env, int *start, int *end);
void		find_end_pos(char *data, int *end, int *is_replace);
char		*get_env_or_status(char *env);
void		replace_home_dir(char **cmd);

/*
** sort_utils.c
*/
void		env_sort(t_list **lst);
t_list		*ft_lstdup(t_list *lst);

/*
** termios_utils.c
*/
void		get_org_term(void);
void		set_org_term(void);
void		set_new_term(void);

/*
** utils.c
*/
t_info		*get_info(void);
void		handler(int signo);
int			ft_strcmp(char *s1, char *s2);
int			ft_isblank(char c);
char		*get_env(char *name);

/*
**	parsing
**	- the function of parsing codes
*/

/*
** env_list.c
*/
t_enode		*new_enode(char *env);
void		env_preprocess(char **envp);

/*
** list.c
*/
t_tok_list	*create_list(void);
void		add_token(t_tok_list **list, t_tok *new_tok);
t_tok		*get_token(t_tok_list *list, int pos);

/*
**	replace_env.c
*/
void		replace_recur(t_node *node);

/*
** semantic.c
*/
int			check_quote(char *str);
int			chk_syntax(t_node *node);

/*
** syntax.c
*/
void		pipeline(int *idx);
void		cmd(int *idx);
void		simple_cmd(int *idx);
void		redirs(int *idx);
void		redir(int *idx);
void		args(int *idx);
void		path(int *idx);
void		filename(int *idx);
int			syntax(void);

/*
** tokenize.c
*/
void		tokenize(t_tok_list **list, char *str);

/*
**	exec
**	- executing commands from AST
*/

/*
** ft_execve.c
*/
void		exec(t_node *node);

/*
** get_cmd_opt.c
*/
char		**get_cmd_opt(t_node *node);

/*
** pipe.c
*/
void		exec_pipe(t_node *node);

/*
** read_tree.c
*/
void		read_tree(t_node *node);

/*
** redir.c
*/
int			connect_redir(void);
int			disconnect_redir(void);
void		redirection(t_node *node);

/*
** exec/heredoc
** - the functions used by heredoc
*/

/*
** heredoc.c
*/
void		start_heredoc(t_node *hdoc_node);

/*
** heredoc_utils.c
*/
t_heredoc	*new_heredoc(t_node *eof);
void		clear_heredoc(void *content);

/*
**	builtin
**	- builtin commands in minishell
*/
void		builtin_cd(t_node *cmd);
void		builtin_echo(t_node *cmd);
void		builtin_env(t_node *cmd);
void		builtin_exit(t_node *cmd);
void		builtin_export(t_node *cmd);
void		builtin_pwd(t_node *cmd);
void		builtin_unset(t_node *cmd);

#endif
