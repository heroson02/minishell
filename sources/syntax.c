/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/21 21:43:14 by hyojlee          ###   ########.fr       */
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
	if (token && (token->type == REDIR || token->type == HEREDOC))
		redirs(list, idx);
}

void simple_cmd(t_tok_list *list, int *idx)
{
	t_tok	*token;

	token = get_token(list, *idx);
	if (!token || token->type == REDIR || token->type == PIPE || token->type == HEREDOC)
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
	if (token && (token->type == REDIR || token->type == HEREDOC))
	{
		redir(list, idx);
		redirs(list, idx);
	}
}

void redir(t_tok_list *list, int *idx)
{
	t_tok	*token;

	token = get_token(list, *idx);
	if (token->next && (token->next->type == REDIR) || token->next->type == HEREDOC)
	{ 
		printf("error\n"); 
		exit(1);
	}
	// error();
	(*idx)++;
	filename(list, idx);
}

// 명령어의 인자(또는 옵션)
// 명령어의 자식에 붙임
void args(t_tok_list *list, int *idx)
{
	t_tok	*token;

	token = get_token(list, *idx);
	if (token->type == REDIR || token->type == PIPE || token->type == HEREDOC)
		return ;
	(*idx)++;
	if (token->next)
		args(list, idx);
}

// 명령어, 실행파일 이름
// 파이프 뒤에 나오면 오른쪽에,
// 리다이렉션 뒤에 나오면 왼쪽에 붙어야함.
void path(t_tok_list *list, int *idx)
{
	(void)list;
	(*idx)++;
}

// 진짜 파일 이름
// 항상 리다이렉션 뒤에 나오므로 마지막 리다이렉션을 찾아서 리다이렉션 노드 오른쪽에 붙임.
void filename(t_tok_list *list, int *idx)
{
	if (get_token(list, *idx)->type == PIPE)
		return ;
	(void)list;
	(*idx)++;
}
