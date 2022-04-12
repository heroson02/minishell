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

# define TRUE	1
# define FALSE	0

# define REPLACE 1

typedef enum	e_type
{
	TOKEN = -1,
	PIPE = '|',
	LESS = '<',
	GREAT = '>',
	SQUOTE = '\'',
	DQUOTE = '\"',
	DLESS = ' ',
	DGREAT = '\\'
}	t_type;

typedef enum	e_state
{
	STATE_GEN,
	STATE_SQUO,
	STATE_DQUO
}	t_state;

typedef struct s_tok
{
	char	*data;
	t_type	type;
	struct s_tok *next;
}	t_tok;

typedef struct s_list
{
	t_tok	*head;
	int		size;
}	t_list;



#endif
