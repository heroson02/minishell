/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/19 17:50:27 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
 * 22.04.18
 * 각각의 논터미널 기호에 대한 함수 작성
 * PIPELINE, CMD, SIMPLE_CMD, REDIR, PATH, FILENAME
 * 토큰 리스트와 현재 토큰의 위치를 알아야 됨.
 * 
 * 결국 PATH와 FILENAME이 터미널 기호로 치환되므로 
 * 두 함수에서 accept(), error() 판별을 해주면 됨.
 */

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
**				| empty
**	
**  <ARGS> := WORD
**			| WORD <ARGS>
**
**	<PATH> := WORD
**	
**	<FILENAME> := WORD
*/

// void	pipeline(t_tok_list **list, int *idx)
// {
// 	if (!list || idx == 0 && get_token(*list, idx)->type == PIPE)
// 		error();
// 	command(list, idx);
// 	if (get_token(*list, idx) && get_token(*list, idx)->type == PIPE)
// 		pipeline(list, ++(*idx));
// }

// void	command(t_tok_list **list, int *idx)
// {
// 	t_tok	*token;

// 	simple_cmd(list, idx);
// 	token = get_token(*list, idx);
// 	//리다이렉션 조건문
// 	if (token->type == LESS || token->type == GREAT || token->type == DLESS || token->type == DGREAT)
// 		redirection(*list, ++(*idx));
// 	// if (get_token(*list, idx) && get_token(*list, idx)->type != PIPE)
// 	// 	command(list, ++(*idx));
// }

// void	simple_cmd(t_tok_list **list, int *idx)
// {
// 	t_tok	*token;

// 	token = get_token(*list, idx);
//  	if (token->type == LESS || token->type == GREAT ||
// 	 	token->type == DLESS || token->type == DGREAT || token->type == PIPE)
// 		return ;
// 	path(*list, idx);
// 	if (get_token(*list, idx))
// 		args(list, ++(*idx));
// }

// void	args(t_tok_list **list, int *idx)
// {
// 	t_tok	*token;

// 	token = get_token(*list, idx);
// 	if (token->type == LESS || token->type == GREAT ||
// 		token->type == DLESS || token->type == DGREAT || token->type == PIPE)
// 		return ;
// 	// if (token->next && !(token->type == LESS || token->type == GREAT ||
// 	// 	token->type == DLESS || token->type == DGREAT || token->type == PIPE))
// 	if (token->next)
// 		args(list, ++(*idx));
// }

// void	path(t_tok_list **list, int *idx)
// {
	
// }

// void	redirection(t_tok_list **list, int *idx)
// {
// 	t_tok	*token;

// 	token = get_token(*list, idx);
// 	if (token && token->type == )

// }

// void	filename(t_tok_list **list, int *idx)
// {

// }

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