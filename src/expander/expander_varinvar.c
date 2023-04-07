#include "../../include/minishell.h"

int	is_var(char *str, int i)
{
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	while (str[i] && str[i] != ' ')
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	var_in_str(char *str)
{
	int	i;
	int	sq_flag;

	sq_flag = 0;
	i = 0;
	while (str[i])
	{
		if (sq_flag && str[i] == '\'')
			sq_flag = 0;
		else if (!sq_flag && str[i] == '\'')
			sq_flag = 1;
		if (str[i] == '$' && !sq_flag && str[i + 1])
			if (is_var(str, i + 1))
				return (1);
		i++;
	}
	return (0);
}

char	**mini_lexer(char *str)
{
	char	**split;
	int		strnumber;

	if (quote_is_unbalanced(recognize_quote(str, '\''),
			recognize_quote(str, '\"')) == -1)
		return (0);
	str = ft_strtrim(str, "\n\t\v\f\r ");
	strnumber = countstrs(str) + 1;
	split = NULL;
	split = allocate(split, strnumber);
	create_strings(split, str);
	split[strnumber] = NULL;
	free(str);
	return (split);
}

char	**replace_args(char **c_args, char **args)
{
	int		i;
	int		j;
	int		arg_len;
	char	**new_args;

	i = 0;
	j = 0;
	arg_len = ft_2darraylen(c_args) + ft_2darraylen(args);
	new_args = (char **) malloc (sizeof(char *) * (arg_len));
	if (!new_args)
		return (NULL);
	while (c_args && c_args[i])
		new_args[i++] = ft_strdup(c_args[j++]);
	j = 1;
	while (args[j])
		new_args[i++] = ft_strdup(args[j++]);
	new_args[i] = NULL;
	return (new_args);
}

int	only_whitespace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_iswhitespace(s[i]))
			return (0);
		i++;
	}
	return (1);
}
