/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yson <yson@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 20:48:28 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/12 21:20:43 by yson             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_info	*get_info(void)
{
	static	t_info info;

	return (&info);
}

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		// printf("\n");
		// rl_on_new_line();
		// rl_replace_line("", 0);
		// rl_redisplay();
		get_info()->exitcode = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}	
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	len;

	len = ft_strlen(s1);
	if (len < ft_strlen(s2))
		len = ft_strlen(s2);
	return (ft_memcmp(s1, s2, len));
}

int	ft_isblank(char c)
{
	if (c == ' ' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == '\t')
		return (1);
	return (0);
}

/*
** 환경변수 가져오는 함수 수정본
** 환경변수($HOME와 같은 애들) 값을 치환하기 위해 만들어둔 함수
** 환경변수가 존재하지 않으면 그냥 빈 문자열을 출력하므로 (echo $HELLO)
** name에 해당하는 환경변수가 존재하지 않으면 빈 문자열을 출력한다.
*/
char	*get_env(char *name)
{
	t_list	*cur;
	t_info	*info;

	info = get_info();
	cur = info->env_list;
	while (cur)
	{
		if (!ft_strcmp(((t_enode *)cur->content)->key, name))
			return (((t_enode *)cur->content)->value);
		cur = cur->next;
	}
	return ("");
}
