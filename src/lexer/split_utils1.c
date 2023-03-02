#include "../include/minishell.h"

char	**allocate(char **split, int strnumber)
{
	int	i;

	i = 0;
	split = malloc(sizeof(char *) * (strnumber + 1));
	while (i < strnumber + 1)
	{
		split[i] = NULL;
		i++;
	}
	return (split);
}

char	**makestring(char **split, char *str, int start, int i)
{
	int	count;
	int	range;

	count = 0;
	range = i - start;
	while (split[count])
		count++;
	split[count] = malloc(range + 1);
	split[count][range] = '\0';
	ft_strlcpy(split[count], str + start, range + 1);
	return (split);
}

int	jump_delimiters(char *str, int *i)
{
	int	start;
	int	redir;

	start = *i;
	if (ft_iswhitespace(str[*i]))
	{
		while (ft_iswhitespace(str[*i]))
			*i += 1;
		redir = jump_redir(str, i);
		while (ft_iswhitespace(str[*i]))
			*i += 1;
		if (redir)
			return (redir);
		return (1);
	}
	redir = jump_redir(str, i);
	if (redir)
	{
		while (ft_iswhitespace(str[*i]))
			*i += 1;
		return (redir);
	}
	return (0);
}

int	jump_redir(char *str, int *i)
{
	int	count;

	count = 0;
	if (*i == 0)
		count = 1;
	// if (is_char(str[*i], '<'))
	// {
		// while (is_char(str[*i], '<'))
		// 	*i += 1;
		// if (str[*i] == '\0')
		// 	count++;
		// return (2 - count);
	// }
	if (is_char(str[*i], '>') || is_char(str[*i], '<') || is_char(str[*i], '|'))
	{
		while (is_char(str[*i], '>') || is_char(str[*i], '<') || is_char(str[*i], '|'))
			*i += 1;
		if (str[*i] == '\0')
			count++;
		return (2 - count);
	}
	return (0);
}
