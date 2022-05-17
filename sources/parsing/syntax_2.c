/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/13 18:08:13 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

// 명령어의 인자(또는 옵션)
// 명령어의 자식에 붙임
void	args(int *idx)
{
	t_tok	*token;
	t_node	*node;
	t_info	*info;

	info = get_info(); //
	token = get_token(info->list, *idx);
	if (!token)
		return ;
	if (token->type == REDIR || token->type == PIPE || token->type == HEREDOC)
		return ;
	node = create_node(token);
	insert_path(info->tree, node);
	(*idx)++;
	if (token->next)
		args(idx);
}

// 명령어, 실행파일 이름
// 파이프 뒤에 나오면 오른쪽에,
// 리다이렉션 뒤에 나오면 왼쪽에 붙어야함.
void	path(int *idx)
{
	t_tok	*token;
	t_node	*node;
	t_info	*info;

	info = get_info();
	token = get_token(info->list, *idx);
	if (!token)
		return ;
	node = create_node(token);
	insert_path(info->tree, node);
	(*idx)++;
}

// 진짜 파일 이름
// 항상 리다이렉션 뒤에 나오므로 마지막 리다이렉션을 찾아서 리다이렉션 노드 오른쪽에 붙임.
void	filename(int *idx)
{
	t_tok	*token;
	t_node	*node;
	t_info	*info;

	info = get_info();
	token = get_token(info->list, *idx);
	if (!token || token->type == PIPE)
		return ;
	node = create_node(token);
	insert_filename(info->tree, node);
	(*idx)++;
}

int	syntax(void)
{
	int		idx;
	t_info	*info;

	info = get_info();
	idx = 0;
	if (!info || !info->list || !info->tree)
		return (FALSE);
	pipeline(&idx);
	return (TRUE);
}
