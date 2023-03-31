#include "../../include/minishell.h"

int	is_delimiter(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (c);
	return (0);
}

int	jump_delimiter_split(char **split, char *str, int *start, int *i)
{
	if (is_delimiter(str[*i]) || ft_iswhitespace(str[*i]))
	{
		while (is_delimiter(str[*i]) || ft_iswhitespace(str[*i]))
			(*i)++;
		split = makestring(split, str, start, i);
		*start = *i;
		return (1);
	}
	return (0);
}

int	switch_flags(int *flag, int quote, int *keep_quote)
{
	if (*flag == 0)
	{
		if (quote == 3)
			*flag = 3;
		else
			*flag = 1;
		*keep_quote = quote;
		return (1);
	}
	else if (*flag == 1 && quote == *keep_quote)
	{
		*flag = 0;
		return (1);
	}
	return (0);
}

int	handle_quote(char *str, int *i, int *flag, int *keep_quote)
{
	int	quote;

	quote = 0;
	if ((str[*i] == '<' || str[*i] == '>' || str[*i] == '|') && *flag == 4)
		*flag = 0;
	if (is_char(str[*i], '\"'))
	{
		quote = 1;
		switch_flags(flag, quote, keep_quote);
		(*i)++;
		return (1);
	}
	if (is_char(str[*i], '\''))
	{
		quote = 2;
		switch_flags(flag, quote, keep_quote);
		(*i)++;
		return (1);
	}
	return (0);
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
