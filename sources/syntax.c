/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/26 17:18:34 by hyojlee          ###   ########.fr       */
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

int	syntax(t_info *info)
{
	int	idx;
	
	idx = 0;
	if (!info || !info->list || !info->tree)
		return (FALSE);
	pipeline(info, &idx);
	return (TRUE);
}

void pipeline(t_info *info, int *idx)
{	
	t_tok	*token;
	t_node	*node;

	cmd(info, idx);
	token = get_token(info->list, *idx);
	if (token && token->type == PIPE && ++(*idx))
	{
		node = create_node(token);
		insert_pipe_heredoc(info->tree, node);
		// if (token->next && token->next->type == PIPE)
		// {
		// 	printf("error\n");
		// 	exit(258);
		// 	//error();
		// }
		pipeline(info, idx);
	}
	else if (token)
		pipeline(info, idx);
}

void cmd(t_info *info, int *idx)
{
	t_tok	*token;

	simple_cmd(info, idx);
	token = get_token(info->list, *idx);
	if (token && (token->type == REDIR || token->type == HEREDOC))
		redirs(info, idx);
}

void simple_cmd(t_info *info, int *idx)
{
	t_tok	*token;

	token = get_token(info->list, *idx);
	if (!token || token->type == REDIR || token->type == PIPE || token->type == HEREDOC)
		return ;
	path(info, idx);
	token = get_token(info->list, *idx);
	if (token)
		args(info, idx);
}

void	redirs(t_info *info, int *idx)
{
	t_tok	*token;
	
	token = get_token(info->list, *idx);
	if (token && token->type == PIPE)
		return ;
	if (token && (token->type == REDIR || token->type == HEREDOC))
	{
		redir(info, idx);
		redirs(info, idx);
	}
}

void redir(t_info *info, int *idx)
{
	t_tok	*token;
	t_node	*node;

	token = get_token(info->list, *idx);
	if (!token)
		return ;
	// if (token->next && (token->next->type == REDIR || token->next->type == HEREDOC))
	// { 
	// 	printf("error\n"); 
	// 	exit(1);
	// }
	// error();
	node = create_node(token);
	if (token->type == REDIR)
		insert_redir(info->tree, node);
	else
		insert_pipe_heredoc(info->tree, node);
	(*idx)++;
	filename(info, idx);
}

// 명령어의 인자(또는 옵션)
// 명령어의 자식에 붙임
void args(t_info *info, int *idx)
{
	t_tok	*token;
	t_node	*node;

	token = get_token(info->list, *idx);
	if (!token)
		return ;
	if (token->type == REDIR || token->type == PIPE || token->type == HEREDOC)
		return ;
	node = create_node(token);
	insert_path(info->tree, node);
	(*idx)++;
	if (token->next)
		args(info, idx);
}

// 명령어, 실행파일 이름
// 파이프 뒤에 나오면 오른쪽에,
// 리다이렉션 뒤에 나오면 왼쪽에 붙어야함.
void path(t_info *info, int *idx)
{
	t_tok	*token;
	t_node	*node;

	token = get_token(info->list, *idx);
	if (!token)
		return ;
	node = create_node(token);
	insert_path(info->tree, node);
	(*idx)++;
}

// 진짜 파일 이름
// 항상 리다이렉션 뒤에 나오므로 마지막 리다이렉션을 찾아서 리다이렉션 노드 오른쪽에 붙임.
void filename(t_info *info, int *idx)
{
	t_tok	*token;
	t_node	*node;

	token = get_token(info->list, *idx);
	if (!token || token->type == PIPE)
		return ;
	node = create_node(token);
	insert_filename(info->tree, node);
	(*idx)++;
}
