/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:54:38 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/06 15:54:40 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./minishell.h"
# include "../libft/libft.h"
#include <stdio.h>
# define WORD	0
# define PIPE	1
# define REDIR	2

/*
** 띄어쓰기 치환-> 따옴표 안에 있는 경우는 모두 치환해야함.
*/

// static char	*replace_space(char *str)
// {
// 	int	idx;

// 	idx = 0;
// 	while (str[idx])
// 	{
// 		if (str[idx] == 1)
// 			str[idx] = ' ';
// 		idx++;
// 	}
// 	return (str);
// }



static int	decide_type(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[0] == '\"' || str[0] == '\'')
		return (WORD);

	if (!ft_strncmp(str, "|", len))
		return (PIPE);
	else if (str[1] == "|")
		print_err("syntax error", 1);
	
	if (!ft_strncmp(str, "<", len) || !ft_strncmp(str, "<<", len))
		return (REDIR);
	else if (str[3] && str[3] == "<")
		print_err("syntax error", 1);
	
	if (!ft_strncmp(str, ">", len) || !ft_strncmp(str, ">>", len))
		return (REDIR);
	else if (str[3] && str[3] == ">")
		print_err("syntax error", 1);
	
	return (WORD);
}
/*
리다이렉션과 파이프는 띄어쓰기만으로 토큰화하면 안된다.
리다이렉션, 파이프 기준으로도 잘라야함.
*/

// void	tokenize(char **split, t_list *list)
// {
// 	int i;
// 	t_data data;

// 	i = 0;
// 	while (split[i])
// 	{
// 		data.str = replace_space(split[i]);
// 		data.type = decide_type(split[i]);
// 		add_token(list, data);
// 		i++;
// 	}
	
// }

// void	parse(char *line, t_list *list)
// {
// 	if (chk_quote(line) == FALSE)
// 		print_err("Quote is unclosed", 1);
// 	tokenize(ft_split(line, " "), list);
// }

int main()
{
	printf("%d\n", decide_type("||"));
}