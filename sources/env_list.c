/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:35:39 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/01 16:16:52 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

//환경변수를 이름과 값을 구분해서 t_enode 구조체에 저장
void	free_enode(void *node)
{
	t_enode	*enode;
	
	enode = (t_enode *)node;
	free(enode->key);
	enode->key = 0;
	free(enode->value);
	enode->value = 0;
	free(enode);
	enode = 0; // ft_bzero(enode, sizeof(t_enode));
}

t_enode	*new_enode(char *env)
{
	t_enode	*result;
	char	*value;

	result = (t_enode *)malloc(sizeof(t_enode));
	if (!result)
		return (0);
	value = ft_strchr(env, '=');
	result->key = ft_substr(env, 0, ft_strlen(env) - ft_strlen(value));
	result->value = ft_substr(value, 1, ft_strlen(value) - 1);
	return (result);
}

void	env_preprocess(t_info *info, char **envp)
{
	t_list	*head;
	int		i;

	i = 1;
	head = ft_lstnew(new_enode(envp[0]));
	info->env_list = head;
	while (envp[i])
	{
		ft_lstadd_back(&head, ft_lstnew(new_enode(envp[i])));
		i++;
	}
}

// 환경변수 가져오는 함수 수정본
// 환경변수($HOME와 같은 애들) 값을 치환하기 위해 만들어둔 함수
// 환경변수가 존재하지 않으면 그냥 빈 문자열을 출력하므로 (echo $HELLO)
// name에 해당하는 환경변수가 존재하지 않으면 빈 문자열을 출력한다.
char	*get_env(t_info *info, char *name)
{
	t_list	*cur;

	cur = info->env_list;
	while (cur)
	{
		if (!ft_strcmp(((t_enode *)cur->content)->key, name))
			return (((t_enode *)cur->content)->value);
		cur = cur->next;
	}
	return ("");
}
