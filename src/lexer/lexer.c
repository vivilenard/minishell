#include "../../include/minishell.h"

int	do_shit(char **split, char *str, int *i, int *start)
{
	if (is_delimiter(str[*i]))
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
	int	is_split;

	i = 0;
	start = 0;
	flag = 0;
	keep_quote = 0;
	is_split = 0;
	//printf("create\n");
	jump_delimiter_split(split, str, &start, &i);
	while (str[i])
	{
		handle_quote(str, &i, &flag, &keep_quote);
		// if (flag == 0 || flag == 3)
		if (flag != 1)
			is_split = do_shit(split, str, &i, &start);
		if (is_split && flag == 3)
			flag = 4;
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
		// if (flag == 0 || flag == 3)
		if (flag != 1)
		{
			n = jump_delimiters(str, &i);
			count += n;
			if (n)
			{
				if (flag == 3)
					flag = 4;
				i--;
			}
		}
		if (str[i] && !handle_quote(str, &i, &flag, &keep_quote))
			i++;
	}
	return (count);
}

void	count_quote(char *str, int i, int *singlequote, int *doublequote)
{
	if (str[i] == '\'')
		(*singlequote)++;
	if (str[i] == '\"')
		(*doublequote)++;
}

int	quote_is_unbalanced(int singlequote, int doublequote)
{
	if (singlequote % 2 > 0 || doublequote % 2 > 0)
	{
		//printf("sq %d, dq %d\n", singlequote, doublequote);
		ft_putstr_fd("please end quote ", 2);
		if (singlequote % 2 > 0)
			ft_putendl_fd(" \' ", 2);
		else
			ft_putendl_fd(" \" ", 2);
		return (-1);
	}
	return (0);
}

int	quote_counter(char *str)
{
	int	i;
	int	sq;
	int	dq;
	int	flag;

	i = 0;
	sq = 0;
	dq = 0;
	flag = 0;
	while (str && str[i])
	{
		if (ft_strncmp(str + i, "echo ", 5) == 0)
		{
			flag = 4;
			i += 4;
		}
		if (flag == 0)
			count_quote(str, i, &sq, &dq);
		if (str[i] == '|')
			flag = 0;
		i++;
	}
	return (quote_is_unbalanced(sq, dq));
}
int	lexer(char *str, t_data *data)
{
	char	**split;
	int		strnumber;

	if (quote_counter(str) == -1)
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

// int	quote_counter(char *str)
// {
// 	int	i;
// 	int	flag;
// 	int	keep_quote;
// 	int singlequote;
// 	int	doublequote;

// 	i = 0;
// 	flag = 0;
// 	keep_quote = 0;
// 	singlequote = 0;
// 	doublequote = 0;
// 	while(str && str[i])
// 	{
// 		if (handle_quote(str, &i, &flag, &keep_quote))
// 			i--;
// 		if (jump_delimiters(str, &i) && flag == 3)
// 		{
// 			flag = 4;
// 		}
// 		if (flag != 4)
// 			count_quote(str, i, &singlequote, &doublequote);
// 		//printf("%d, %d\n", flag, doublequote);
// 		i++;
// 	}
// 	return (quote_is_unbalanced(singlequote, doublequote));
// }