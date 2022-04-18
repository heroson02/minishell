/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:32:20 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/14 20:24:00 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

t_type	get_type(char *str, int len)
{
	char	c;

	c = *str;
	if (c == PIPE)
		return (PIPE);
	else if (c == LESS && len > 1)
		return (DLESS);
	else if (c == GREAT && len > 1)
		return (DGREAT);
	else if (c == LESS)
		return (LESS);
	else if (c == GREAT)
		return (GREAT);
	else if (c == SQUOTE)
		return (SQUOTE);
	else if (c == DQUOTE)
		return (DQUOTE);
	else
		return (TOKEN);
}

char	*init_token(t_tok_list **list, char *start, char *end)
{
	t_tok	*new_tok;
	int		len;

	len = end - start + 1;
	new_tok = (t_tok *)malloc(sizeof(t_tok));
	if (!new_tok)
		print_err("malloc error", 1);
	ft_bzero(new_tok, sizeof(t_tok));
	new_tok->data = ft_substr(start, 0, len);
	new_tok->type = get_type(start, len);
	add_token(list, new_tok);
	return (end + 1);
}

void	tokenize(t_tok_list **list, char *str)
{
	char *end;

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
// int main()
// {
// 	t_tok_list	*list;
// 	t_tok		*curr;

// 	list = create_list();
// 	tokenize(&list, "<file1cmd\"hello world!\"||file2>cmd2   ");
// 	curr = list->head;
// 	while (curr)
// 	{
// 		printf("%s\n", curr->data);
// 		curr = curr->next;
// 	}
	
// }