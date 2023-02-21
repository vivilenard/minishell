/* Splits at whitespaces and redirections signs. Until the function encounters
a null terminator or Pipe-Sign.

When encountering a redirection sign the token will be flagged with the
corresponding redirection sign.

If "echo" is encountered everything after the option is saved into one string
until the function finds a redirection, pipe or NULL.

If " or ' is encountered, the function does not split until another " or '
is present in the string.

The function then continues */


/*TO DO:
	- echo
	- quotes
*/

#include "../include/minishell.h"

char **allocate(char **split, int strnumber)
{
	int i;

	i = 0;
	split = malloc(sizeof(char *) * (strnumber + 1));
	while (i < strnumber + 1)
	{
		split[i] = NULL;
		i++;
	}
	return (split);
}


int countstrs(char *str)
{
	int i;
	int count;
	int n;
	int flag;

	i = 0;
	count = 0;
	n = 0;
	flag = 0;
	while (str[i])
	{
		if (is_char(str[i], '\''))
			switch_flag(&flag);
		if (flag == 0)
		{
			n = jump_delimiters(str, &i);
			count += n;
			if (n)
				i--;
		}
		i++;
	}
	return (count);
}

int	jump_delimiter(char **split, char *str, int *start, int *i)
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

void switch_flags(int *flag, int i)
{
	if (flag[i] == 0)
		flag[i] = 1;
	else if (flag[i] == 1)
		flag[i] = 0;
}

int	handle_quote(char *str, int i, int *flag, int *keep_quote)
{
	if (is_char(str[i], '\"'))
	{
		if (flag[0] == 0)
			*keep_quote = 0;
		if (*keep_quote == 0)
			switch_flags(flag, 0);
		printf("%c, %d, %d\n", str[i], flag[0], flag[1]);
		return (1);
	}
	if (is_char(str[i], '\''))
	{
		if (flag[1] == 0)
			*keep_quote = 1;
		if (*keep_quote == 1)
			switch_flags(flag, 1);
		printf("%c, %d, %d\n", str[i], flag[0], flag[1]);
		return (1);
	}
	//printf("%c, %d\n", str[i], *flag);
	return (0);
}

int	do_shit(char **split, char *str, int *i, int *start)
{
	if (is_delimiter(str[*i]))
	{
		split = makestring(split, str, *start, *i);
		while(ft_iswhitespace(str[*i]))
			(*i)++;
		*start = *i;
		if (jump_redir(str, i))
		 	split = makestring(split, str, *start, *i);
		while(ft_iswhitespace(str[*i]))
			(*i)++;
		*start = *i;
		return (1);
	}
	return (0);
}

char **create_strings(char **split, char *str)
{
	int i;
	int flag[2] = {0, 0};
	int	keep_quote;
	int	start;

	i = 0;
	start = 0;
	keep_quote = 5;
	jump_delimiter(split, str, &start, &i);
	while (str[i])
	{
		handle_quote(str, i, flag, &keep_quote);
		//printf("%c, %d\n", str[i], flag);
		if (flag[0] == 0)
			do_shit(split, str, &i, &start);
		handle_quote(str, i, flag, &keep_quote);
		i++;
	}
	split = makestring(split, str, start, i);
	return (split);
}

char **split_token (char *str)
{
	char **split;
	int strnumber;

	split = NULL;
	str = ft_strtrim(str, "\n\t\v\f\r ");
	strnumber = countstrs(str) + 1;
	printf("%d\n", strnumber);
	split = allocate(split, strnumber);
	create_strings(split, str);
	split[strnumber] = NULL;
	return (split);
}
