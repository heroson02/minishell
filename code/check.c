/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:32:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/06 16:32:21 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

t_type	get_type(char c)
{
	if (c == PIPE)
		return (PIPE);
	else if (c == LESS)
		return (LESS);
	else if (c == GREAT)
		return (GREAT);
	else if (c == SQUOTE)
		return (SQUOTE);
	else if (c == DQUOTE)
		return (DQUOTE);
	else if (ft_isblank(c))
		return (SPACE);
	else
		return (TOKEN);
}

// t_tok	*init_token(t_data data, t_type type)
// {
// 	t_tok	*new_tok;

// 	new_tok = (t_tok *)malloc(sizeof(t_tok));
// 	if (!new_tok)
// 		print_err("malloc error", 1);
// 	ft_bzero(new_tok, sizeof(t_tok));
// 	new_tok->data = data;
// 	new_tok->type = type;
// 	return (new_tok);
// }

t_tok	*init_token(char *line, int start, int end, t_type type)
{
	t_tok	*new_tok;

	new_tok = (t_tok *)malloc(sizeof(t_tok));
	if (!new_tok)
		print_err("malloc error", 1);
	ft_bzero(new_tok, sizeof(t_tok));
	new_tok->data = ft_substr(line, start, end - start + 1);
	if (!new_tok->data)
		print_err("malloc error", 1);
	new_tok->type = type;
	return (new_tok);
}

int	chk_quote(char *line)
{
	int		start;
	int		end;
	t_type	cur;

	start = 0;
	end = 0;
	while (line[start])
	{
		while (ft_isblank(line[end])) //들어온 공백은 날림
			end++;
		start = end;
		while (line[end] && ft_strchr("\'\"", line[start]))
		{
			if (ft_strchr("\'\"", line[end]) &&
				line[end] == line[start])
				break ;
			end++;
		}
		while (line[end] && !ft_strchr("\'\"><| ", line[end]))
			end++;
		if (line[end] && ft_strchr("><|", line[end]))
		{
			if (start != end)
				end--;
		}
		init_token(line, start, end, get_type(line[start]));
		end++;
	}
}


void	tokenize(char *str)
{
	t_type	t;
	char *end;

	while (*str)
	{
		while (*str == ' ')
			str++;
		t = get_type(*str);
		end = str;
		if (t == TOKEN)
		{
			while (*(end + 1) && !ft_strchr(" |<>", *(end + 1)))
				end++;
			if (*(end + 1) && ft_strchr(" |<>", *(end + 1)))
			{
				//토큰화
				continue ;
			}
		}
		if (t == PIPE || t == LESS || t == GREAT)
		{
			if (*end && *end == *(end + 1), ft_strchr("<>", *end))
				end++;
			//토큰화
			continue ;
		}
		if (t == SQUOTE || t == DQUOTE)
		{
			while (*(end + 1) && !ft_strchr("\'\"", *(end + 1)))
				end++;
			//토큰화
			continue ;
		}
	}
	
}