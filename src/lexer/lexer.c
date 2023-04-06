#include "../../include/minishell.h"

int	do_shit(char **split, char *str, int *i, int *start)
{
	if (is_delimiter(str[*i]) || ft_iswhitespace(str[*i]))
	{
		split = makestring(split, str, start, i);
		if (is_delimiter(str[*i]))
		{
			while (is_delimiter(str[*i]))
				(*i)++;
			if (str[*i] && !is_delimiter(str[*i]) && !ft_iswhitespace(str[*i]))
				split = makestring(split, str, start, i);
			(*i)--;
		}
		return (1);
	}
	return (0);
}

char	**create_strings(char **split, char *str)
{
	int	i;
	int	flag;
	int	keep_quote;
	int	start;

	i = 0;
	flag = 0;
	keep_quote = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	start = i;
	jump_delimiter_split(split, str, &start, &i);
	if (str[i])
	{
		while (str[i])
		{
			handle_quote(str, &i, &flag, &keep_quote);
			if (flag != 1)
				do_shit(split, str, &i, &start);
			if (str[i] && !handle_quote(str, &i, &flag, &keep_quote))
				i++;
		}
		split = makestring(split, str, &start, &i);
	}
	return (split);
}

int	countstrs(char *str)
{
	int	i;
	int	count;
	int	n;
	int	flag;
	int	keep_quote;

	i = 0;
	count = 0;
	n = 0;
	flag = 0;
	keep_quote = 0;
	while (str[i])
	{
		handle_quote(str, &i, &flag, &keep_quote);
		if (flag != 1)
		{
			n = jump_delimiters(str, &i);
			count += n;
			if (n)
				i--;
		}
		if (str[i] && !handle_quote(str, &i, &flag, &keep_quote))
			i++;
	}
	return (count);
}

int	recognize_quote(char *str, char c)
{
	int	i;
	int	keep_quote;
	int	count;
	int	flag;
	int	flagbegin;

	keep_quote = 0;
	count = 0;
	flag = 0;
	i = 0;
	while (str[i])
	{
		flagbegin = flag;
		if (is_char(str[i], '\"'))
			switch_flags(&flag, 1, &keep_quote);
		else if (is_char(str[i], '\''))
			switch_flags(&flag, 2, &keep_quote);
		if (flag - flagbegin != 0 && str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	lexer(char *str, t_data *data)
{
	char	**split;
	int		strnumber;
	char	*tmp;

	if (quote_is_unbalanced(recognize_quote(str, '\''),
			recognize_quote(str, '\"')) == -1)
		return (0);
	str = ft_strtrim(tmp, "\n\t\v\f\r ");
	strnumber = countstrs(str) + 1;
	printf("count %d\n", strnumber);
	split = NULL;
	split = allocate(split, strnumber);
	create_strings(split, str);
	split[strnumber] = NULL;
	free(str);
	// ft_free2d(split);
	// exit (0);
	if (!load_tokens(split, data))
		return (free_data(data), EXIT_FAILURE);
	return (1);
}
