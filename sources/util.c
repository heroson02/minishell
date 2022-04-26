/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyojlee <hyojlee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:55:42 by hyojlee           #+#    #+#             */
/*   Updated: 2022/04/26 13:35:21 by hyojlee          ###   ########.fr       */
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

// 

static inline void	padding(char c, int n)
{
	int		i;

	i = -1;
	while (++i < n)
	{
		ft_putchar_fd(c, STDOUT_FILENO);
		ft_putchar_fd(c, STDOUT_FILENO);
	}
}

void	jputendl(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}


/*
** as_syntax ()			- Print the Information of Syntax Node on the Screen
**
** return				- void
** syntax				- Specific Syntax Node
** level				- Depth of the Syntax Node for Padding
*/

void	as_syntax(t_node *syntax, int level)
{
	if (syntax == NULL)
	{
		padding('\t', level);
		jputendl("NIL", STDOUT_FILENO);
	}
	else
	{
		as_syntax(syntax->right, level + 1);
		padding('\t', level);
		jputendl(syntax->data, STDOUT_FILENO);
		as_syntax(syntax->left, level + 1);
	}
}

/*
** as_print ()			- Print the Total Syntax Nodes of AS Tree
**
** return				- void
** syntax				- AS Tree
*/

void	as_print(t_node *syntax)
{
	as_syntax(syntax, 0);
	jputendl("-------------------------------------------", STDOUT_FILENO);
}
