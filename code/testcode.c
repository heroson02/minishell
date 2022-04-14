# include <stdio.h>

# define REPLACE 1

typedef enum	e_type
{
	TOKEN = -1,
	SPACE = -2,
	PIPE = '|',
	LESS = '<',
	GREAT = '>',
	SQUOTE = '\'',
	DQUOTE = '\"',
	DLESS = -3,
	DGREAT = -4
}	t_type;

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

char	*ft_strchr(const char *str, int c)
{
	char			*s;
	unsigned char	find;

	s = (char *)str;
	find = (unsigned char)c;
	while (*s)
		if ((unsigned char)*s++ == find)
			return (s - 1);
	if ((unsigned char)*s == find)
		return (s);
	return (0);
}

size_t	ft_strlen(char *str)
{
	int idx;

	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

char	*make_token(char *start, char *end)
{
	int len = end - start + 1;

	printf("{");
	while (len > 0 && *start)
	{
		printf("%c", *start);
		start++;
		len--;
	}
	// while (start[len])
	// {
	// 	printf("%c", start[len]);
	// 	len--;
	// }
	
	printf("}\n");
	return (end + 1);
}

void	tokenize(char *str)
{
	char *end;

	while (*str)
	{
		while (*str == ' ')
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
			str = make_token(str, end);
	}
}

int main()
{
	// tokenize("\"echo\" $HOME is");
	// tokenize("\"");
	tokenize("<file1cmd\"hello world!\"||file2>cmd2   ");
	// tokenize("");
}



// 	if (ft_strchr("\'\"", *end))
// 		end = ft_strchr(end + 1, *end);
// 	str = make_token(str, end);