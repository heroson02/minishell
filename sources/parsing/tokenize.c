/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:32:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/17 16:44:49 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_type	get_type(char *str, int len)
{
	char	c;

	c = *str;
	if (c == PIPE)
		return (PIPE);
	else if (c == LESS && len > 1)
		return (HEREDOC);
	else if (c == LESS || c == GREAT)
		return (REDIR);
	else if (c == SQUOTE)
		return (SQUOTE);
	else if (c == DQUOTE)
		return (DQUOTE);
	else
		return (TOKEN);
}

static char	*init_token(t_tok_list **list, char *start, char *end)
{
	t_tok	*new_tok;
	int		len;

	len = end - start + 1;
	new_tok = (t_tok *)malloc(sizeof(t_tok));
	if (!new_tok)
		print_strerr(errno);
	ft_bzero(new_tok, sizeof(t_tok));
	new_tok->data = ft_substr(start, 0, len);
	new_tok->type = get_type(start, len);
	add_token(list, new_tok);
	return (end + 1);
}

void	tokenize(t_tok_list **list, char *str)
{
	char	*end;

	while (*str)
	{
		while (ft_isblank(*str))
			str++;
		end = str;
		while (*end && !ft_strchr(" |<>", *(end)))
		{
			if (ft_strchr("\'\"", *end))
				end = ft_strchr(end + 1, *end);
			if (!*end || ft_strchr(" |<>", *(end + 1)))
				break ;
			end++;
		}
		if (*end && *end == *(end + 1) && ft_strchr("<>", *(end + 1)))
			end++;
		if (*str)
			str = init_token(list, str, end);
	}
}
