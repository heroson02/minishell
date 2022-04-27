/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:55:42 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/27 21:34:21 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	print_token(t_tok_list *list)
{
	t_tok *curr;
	int idx = 0;

	curr = list->head;
	while (curr)
	{
		printf("(%d/%d): %d\t| %s\n", idx, list->count, curr->type, curr->data);
		idx++;
		curr = curr->next;
	}
}

void	ft_clear(t_info *info)
{
	list_clear(info->list);
	tree_clear(info->tree);
}

char *ft_strcat(char *dest, char *src)
{
	char* p_dest;
	char* p_src;

	p_dest = dest;
	while (*p_dest != '\0')
	{
		p_dest++;
	}
	p_src = src;
	while (*p_src != '\0')
	{
		*p_dest++ = *p_src++;
	}
	*p_dest = '\0';
	return dest;
}

void print_tree_node(t_node* node, bool is_right, char *indent)
{
	char r_indent[512];
	char l_indent[512];
	ft_strlcpy(r_indent, indent , 512);
	ft_strlcpy(l_indent, indent , 512);
	if (node->right != NULL)
	{
		print_tree_node(node->right, true, ft_strcat(r_indent, is_right ? "        " : " |      "));
	}
	printf("%s", indent);
	if (is_right)
	{
		printf(" /");
	}
	else
	{
		printf(" \\");
	}
	printf("----- ");
	printf("[%s]\n", node->data);
	if (node->left != NULL)
	{
		print_tree_node(node->left, false, ft_strcat(l_indent, is_right ? "        " : " |      "));
	}
}

void print_tree(t_node* root)
{
	if (root->right != NULL)
	{
		print_tree_node(root->right, true, "");
	}
	printf("[%s]\n", root->data);
	if (root->left != NULL)
	{
		print_tree_node(root->left, false, "");
	}
}

void	env_preprocess(t_info *info, char **envp)
{
	t_list	*head;
	int		i;

	i = 1;
	head = ft_lstnew(envp[0]);
	info->env_list = head;
	while (envp[i])
	{
		ft_lstadd_back(&head, ft_lstnew(envp[i]));
		i++;
	}
}
