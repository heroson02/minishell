#include "minishell.h"

int	num_of_opt(t_node *node)
{
	int	ret;
	t_node	*tmp;

	ret = 1;
	tmp = node->left;
	while (tmp)
	{
		ret++;
		tmp = tmp->left;
	}
	return (ret);
}

char **get_argv(t_node *node)
{
	int		idx;
	char	**opt;
	t_node	*cur;

	idx = 0;
	cur = node;
	opt = (char **)malloc(sizeof(char *) * (num_of_opt(node) + 1));
	while (cur)
	{
		opt[idx] = ft_strdup(cur->data);
		idx++;
		cur = cur->left;
	}
	opt[idx] = 0;
	return (opt);
}
