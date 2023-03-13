#include "../include/minishell.h"

int	is_delimiter(char c)
{
	if (ft_iswhitespace(c) || c == '<' || c == '>' || c == '|')
		return (c);
	return (0);
}

int	jump_delimiter_split(char **split, char *str, int *start, int *i)
{
	if (is_delimiter(str[*i]))
	{
		while (is_delimiter(str[*i]))
			(*i)++;
		split = makestring(split, str, *start, *i);
		*start = *i;
		return (1);
	}
	return (0);
}

void	switch_flags(int *flag, int quote, int *keep_quote)
{
	if (*flag == 0)
	{
		if (quote == 3)
			*flag = 3;
		else
			*flag = 1;
		*keep_quote = quote;
	}
	else if (*flag == 1 && quote == *keep_quote)
	{
		*flag = 0;
	}
}

int	handle_quote(char *str, int *i, int *flag, int *keep_quote)
{
	int	quote;

	quote = 0;
	//printf("%c, 	flag: %d\n", str[*i], *flag);
	// if (!ft_strncmp(str + *i, "echo", 4))
	// {
	// 	quote = 3;
	// 	switch_flags(flag, quote, keep_quote);
	// 	(*i)++;
	// 	return (1);
	// }
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
 	if (!ft_strncmp(str + *i, "echo", 4))
	{
		quote = 3;
		switch_flags(flag, quote, keep_quote);
		(*i)++;
		return (1);
	}
	return (0);
}
