/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:39:28 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/26 16:44:05 by hyojlee          ###   ########.fr       */
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
# include "../libft/libft.h"

# define REPLACE 1

typedef enum	e_std
{
	STDIN = 0,
	STDOUT,
	STDERR
}	t_std;

typedef enum	e_type
{
	TOKEN = -1,
	BLANK = -2,
	PIPE = '|',
	LESS = '<',
	GREAT = '>',
	SQUOTE = '\'',
	DQUOTE = '\"',
	DLESS = -3,
	DGREAT = -4,
	REDIR = -5,
	CMD = -6,
	HEREDOC = -7
}	t_type;

typedef char	*t_data;

typedef struct s_tok
{
	t_data	data;
	t_type	type;
	struct s_tok *next;
}	t_tok;

typedef struct s_tok_list
{
	t_tok	*head;
	int		count;
}	t_tok_list;

typedef struct s_node
{
	t_data	data;
	t_type	type;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_astree
{
	t_node	*root;
} t_astree;

typedef struct s_info
{
	t_tok_list	*list;
	t_astree	*tree;
}	t_info;

/*
 * main.c
 */
void	print_err(char *str, int exit_status);

/*
** list.c
*/
void	add_token(t_tok_list **list, t_tok *new_tok);
t_tok_list *create_list(void);
t_tok	*get_token(t_tok_list *list, int pos);
void	list_clear(t_tok_list *list);

/*
** check.c
*/
void	tokenize(t_tok_list **list, char *str);
/*
** quotecheck.c
*/
int	check_quote(char *str);

/*
** syntax.c
*/
int		syntax(t_info *info);
void	pipeline(t_info *info, int *idx);
void	cmd(t_info *info, int *idx);
void	simple_cmd(t_info *info, int *idx);
void	redir(t_info *info, int *idx);
void	redirs(t_info *info, int *idx);
void	args(t_info *info, int *idx);
void	path(t_info *info, int *idx);
void	filename(t_info *info, int *idx);

/*
** util.c
*/
void	print_token(t_tok_list *list);
void print_tree(t_node* root);
void	as_print(t_node *syntax);
void	ft_clear(t_info *info);

/*
** astree.c
*/

void		insert_pipe_heredoc(t_astree *tree, t_node *node);
t_node		*create_node(t_tok	*token);
t_astree	*create_tree(void);
void		insert_redir(t_astree *tree, t_node *node);
void 		insert_path(t_astree *tree, t_node *node);
void		insert_filename(t_astree *tree, t_node *node);
void	tree_clear(t_astree *tree);

/*
** semantic.c
*/
int			chk_syntax(t_node *node);
#endif
