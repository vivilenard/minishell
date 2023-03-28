#include "../../include/minishell.h"

int	do_shit(char **split, char *str, int *i, int *start)
{
	if (is_delimiter(str[*i]) || ft_iswhitespace(str[*i]))
	{
		split = makestring(split, str, *start, *i);
		while (ft_iswhitespace(str[*i]))
			(*i)++;
		*start = *i;
		if (jump_redir(str, i))
			split = makestring(split, str, *start, *i);
		while (ft_iswhitespace(str[*i]))
			(*i)++;
		*start = *i;
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
	//int	is_split;

	i = 0;
	start = 0;
	flag = 0;
	keep_quote = 0;
	//is_split = 0;
	jump_delimiter_split(split, str, &start, &i);
	while (str[i])
	{
		handle_quote(str, &i, &flag, &keep_quote);
		if (flag != 1)
			do_shit(split, str, &i, &start);
		// if (is_split && flag == 3)
		// 	flag = 4;
		if (str[i] && !handle_quote(str, &i, &flag, &keep_quote))
			i++;
	}
	split = makestring(split, str, start, i);
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

int	quote_is_unbalanced(int singlequote, int doublequote)
{
	if (singlequote % 2 > 0 || doublequote % 2 > 0)
	{
		ft_putstr_fd("please end quote ", 2);
		if (singlequote % 2 > 0)
			ft_putendl_fd(" \' ", 2);
		else
			ft_putendl_fd(" \" ", 2);
		return (-1);
	}
	return (0);
}


int recognize_quote(char *str, char c)
{
	int	i;
	int keep_quote;
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
	//printf("count %d\n", count);
	return (count);
}

int	lexer(char *str, t_data *data)
{
	char	**split;
	int		strnumber;

	if (quote_is_unbalanced(recognize_quote(str, '\''), recognize_quote(str, '\"')) == -1)
		return (0);
	str = ft_strtrim(str, "\n\t\v\f\r ");
	strnumber = countstrs(str) + 1;
	split = NULL;
	split = allocate(split, strnumber);
	create_strings(split, str);
	split[strnumber] = NULL;
	free(str);
	//ft_put2dstr_fd(split, 2);
	if (!load_tokens(split, data))
		return (free_data(data), EXIT_FAILURE);
	return (1);
}
