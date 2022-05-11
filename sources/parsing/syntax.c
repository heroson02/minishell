/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/11 11:56:32 by hyojlee          ###   ########.fr       */
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

void pipeline(int *idx)
{	
	t_tok	*token;
	t_node	*node;
	t_info	*info;

	info = get_info();
	cmd(idx);
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
		pipeline(idx);
	}
	else if (token)
		pipeline(idx);
}

void cmd(int *idx)
{
	t_tok	*token;
	t_info	*info;

	info = get_info();
	simple_cmd(idx);
	token = get_token(info->list, *idx);
	if (token && (token->type == REDIR || token->type == HEREDOC))
		redirs(idx);
}

void simple_cmd(int *idx)
{
	t_tok	*token;
	t_info	*info;

	info = get_info();
	token = get_token(info->list, *idx);
	if (!token || token->type == REDIR || token->type == PIPE || token->type == HEREDOC)
		return ;
	path(idx);
	token = get_token(info->list, *idx);
	if (token)
		args(idx);
}

void	redirs(int *idx)
{
	t_tok	*token;
	t_info	*info;

	info = get_info();
	token = get_token(info->list, *idx);
	if (token && token->type == PIPE)
		return ;
	if (token && (token->type == REDIR || token->type == HEREDOC))
	{
		redir(idx);
		redirs(idx);
	}
}

void redir(int *idx)
{
	t_tok	*token;
	t_node	*node;
	t_info	*info;

	info = get_info();
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
	filename(idx);
	if (token->type == HEREDOC)
		insert_heredoc_redir();
}
