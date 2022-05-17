/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 11:49:46 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/17 19:31:50 by hyojlee          ###   ########.fr       */
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

void	args(int *idx)
{
	t_tok	*token;
	t_node	*node;
	t_info	*info;

	info = get_info();
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
