/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:39:54 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/01 15:54:18 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASTREE_H
# define ASTREE_H

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

typedef struct s_file
{
	char	*name;
	int		fd;
	int		exist;
	int		in_out;
}	t_file;

typedef struct s_node
{
	t_data	data;
	t_type	type;
	t_file	*file;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

typedef struct s_astree
{
	t_node	*root;
} t_astree;

/*
** astree.c
*/
void		insert_pipe_heredoc(t_astree *tree, t_node *node);
t_node		*create_node(t_tok	*token);
t_astree	*create_tree(void);
void		insert_redir(t_astree *tree, t_node *node);
void 		insert_path(t_astree *tree, t_node *node);
void		insert_filename(t_astree *tree, t_node *node);
void		tree_clear(t_astree *tree);

#endif