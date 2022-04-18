/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/18 11:49:49 by hyojlee          ###   ########.fr       */
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

void pipe()
{
	if (첫번째 토큰 == '|')
		error;
	cmd(idx);
	if (현재토큰 == '|')
		pipe(다음토큰);
}
void cmd()
{
	simple_cmd(idx);
	if (현재토큰 == REDIR)
		redirs();	
}
void simple_cmd()
{
	if (현재토큰 == REDIR || 현재토큰 == PIPE)	//현재 토큰과 문자열을 받는 함수 strchr처럼 비교하는 함수
		return ;
	path();
	if (현재토큰)
		args();
}

void redirs()
{
	if (현재토큰 == PIPE)
		return ;
	if (현재토큰 == REDIR)
		redir(다음토큰);
	if (현재토큰)
		redirs();
}

void redir()
{
	if (현재토큰 == PIPE)
		return ;
	if (현재토큰 == REDIR)
	{
		현재 토큰과 <, <<, >>, >와 비교
		if (다음토큰)
			filename(다음토큰);
		else
			error;
	}
}

void args()
{
	if (현재토큰 == REDIR || 현재토큰 PIPE)
		return ;
	if (다음토큰)
		args();
	else
		return ;
}

void path()
{
	idx++;
}

void filename()
{
	idx++;
}