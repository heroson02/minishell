/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:55:42 by hyojlee           #+#    #+#             */
/*   Updated: 2022/05/04 20:58:23 by hyojlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"
	
static char	*ft_strcat(char *dest, char *src)
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

static void print_tree_node(t_node* node, bool is_right, char *indent)
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

void	print_tree(t_node* root)
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

void	print_err(t_info *info, char *line, int err)
{				
	ft_clear(info);
	free(line);
	line = NULL;
	if (err > 0)
		printf("\033[31m%s\033[0m\n", strerror(errno));
	else
		printf("\033[31mSyntax Error\033[0m\n");
}
