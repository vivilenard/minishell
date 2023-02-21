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
	- nullstr weg
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

int	jump_redir(char *str, int *i)
{
	int count;

	count = 0;
	if (*i == 0)
		count = 1;
	if (is_char(str[*i], '<'))
	{
		while(is_char(str[*i], '<'))
			*i += 1;
		if (str[*i + 1] == '\0')
			count++;
		return (2 - count);
	}
	if (is_char(str[*i], '>'))
	{
		while(is_char(str[*i], '>'))
			*i += 1;
		if (str[*i + 1] == '\0')
			count++;
		return (2 - count);
	}
	return (0);
}

int jump_delimiters(char *str, int *i)
{
	int start;
	int redir;

	start = *i;
	redir = jump_redir(str, i);
	if(ft_iswhitespace(str[*i]))
	{
		while (ft_iswhitespace(str[*i]))
			*i += 1;
		if (redir)
			return (redir);
		return (1);
	}
	if (redir)
	{
		while(ft_iswhitespace(str[*i]))
			*i += 1;
		return (redir);
	}
	return (0);
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
		//printf("when count-> l: %c, c: %d, i: %d\n", str[i], count, i);
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

char **makestring(char **split, char *str, int start, int i)
{
	int count;
	int range;

	count = 0;
	range = i - start;
	while (split[count])
		count++;
	//printf("start: %d, i: %d, range: %d, count: %d, strlen: %zu\n", start, i, range, count, ft_strlen(str));
	split[count] = malloc(range + 1);
	split[count][range] = '\0';
	ft_strlcpy(split[count], str + start, range + 1);
	printf("split: %s\n", split[count]);
	return (split);
}

int	is_delimiter(char c)
{
	if (ft_iswhitespace(c) || c == '<' || c == '>')
		return (c);
	return (0);
}

char **create_strings(char **split, char *str)
{
	int i;
	int n;
	int flag;
	int	start;

	i = 0;
	n = 0;
	flag = 0;
	start = 0;
	if (is_delimiter(str[i]))
	{
		while (is_delimiter(str[i]))
			i++;
		split = makestring(split, str, start, i);
		start = i;
	}
	while (str[i])
	{
		n = 0;
		if (is_char(str[i], '\''))
			switch_flag(&flag);
		if (flag == 0)
		{
			if (is_delimiter(str[i]))
			{
				split = makestring(split, str, start, i);
				while(ft_iswhitespace(str[i]))
					i++;
				start = i;
				if (jump_redir(str, &i))
				 	split = makestring(split, str, start, i);
				while(ft_iswhitespace(str[i]))
					i++;
				start = i;
			}
		}
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
	split = allocate(split, strnumber);
	create_strings(split, str);
	return (split);
}
