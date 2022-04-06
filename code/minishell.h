/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:39:28 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/06 15:39:30 by hyojlee          ###   ########.fr       */
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

# define WORD	0
# define PIPE	1
# define REDIR	2

# define TRUE	1
# define FALSE	0

# define REPLACE 1

typedef struct s_data
{
	int		type;
	char	*str;
}	t_data;

typedef struct s_node
{
	t_data	data;
	t_node	*prev;
	t_node	*next;
}	t_node;

typedef struct s_list
{
	int		count;
	t_node	*head;
	t_node	*tail;
}	t_list;

/*
 * check.c
 */
int	chk_quote(char *line);

/*
 *list.c
 */
t_list	*create_list(void);
t_node	*create_node(t_data data);
void	add_token(t_list *list, t_data data);


#endif
