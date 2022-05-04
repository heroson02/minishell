/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 21:18:00 by hyojlee          ###   ########.fr       */
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
