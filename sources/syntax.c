/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/19 19:17:14 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	<PIPELINE> := <CMD>
**				| <CMD> '|' <PIPELINE>
**	
**	<CMD> := <SIMPLE_CMD>
**			| <SIMPLE_CMD> <REDIRS>
**	
**  <REDIRS> := <REDIR>
**			 | <REDIR> <REDIRS>
**
**	<REDIR> := '<' <FILENAME>
**			| '>' <FILENAME>
**			| '>>' <FILENAME>
**			| '<<' <FILENAME>
**
**	<SIMPLE_CMD> := <PATH>
**				| <PATH> <ARGS>
**	
**  <ARGS> := WORD
**			| WORD <ARGS>
**
**	<PATH> := WORD
**	
**	<FILENAME> := WORD
*/

int	syntax(t_tok_list *list)
{
	int	idx;
	
	idx = 0;
	if (!list)
		return (FALSE);
	pipeline(list, &idx);
	if (get_token(list, idx))
	{
		printf("what token? %s\n", get_token(list, idx)->data);
		return (FALSE);
	}
	return (TRUE);
}

void pipeline(t_tok_list *list, int *idx)
{	
	t_tok	*token;

	cmd(list, idx);
	token = get_token(list, *idx);
	if (token && token->type == PIPE && ++(*idx))
	{
		if (token->next && token->next->type == PIPE)
		{
			printf("error\n");
			exit(258);
			//error();
		}
		pipeline(list, idx);
	}
}

void cmd(t_tok_list *list, int *idx)
{
	t_tok	*token;

	simple_cmd(list, idx);
	token = get_token(list, *idx);
	if (token && token->type == REDIR)
		redirs(list, idx);
}

void simple_cmd(t_tok_list *list, int *idx)
{
	t_tok	*token;

	token = get_token(list, *idx);
	if (!token || token->type == REDIR || token->type == PIPE)
		return ;
	path(list, idx);
	token = get_token(list, *idx);
	if (token)
		args(list, idx);
}

void	redirs(t_tok_list *list, int *idx)
{
	t_tok	*token;
	
	token = get_token(list, *idx);
	if (token && token->type == PIPE)
		return ;
	if (token && token->type == REDIR)
	{
		redir(list, idx);
		redirs(list, idx);
	}
}

void redir(t_tok_list *list, int *idx)
{
	t_tok	*token;

	token = get_token(list, *idx);
	if (token->next && token->next->type == REDIR)
	{ 
		printf("error\n"); 
		exit(1);
	}
	// error();
	(*idx)++;
	filename(list, idx);
}

void args(t_tok_list *list, int *idx)
{
	t_tok	*token;

	token = get_token(list, *idx);
	if (token->type == REDIR || token->type == PIPE)
		return ;
	(*idx)++;
	if (token->next)
		args(list, idx);
}

void path(t_tok_list *list, int *idx)
{
	(void)list;
	(*idx)++;
}

void filename(t_tok_list *list, int *idx)
{
	if (get_token(list, *idx)->type == PIPE)
		return ;
	(void)list;
	(*idx)++;
}
