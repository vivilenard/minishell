#include "../../../include/minishell.h"

int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

int	count_rm_quotes(char *str)
{
	int		i;
	int		count;
	char	current_quote;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	current_quote = '\0';
	while (str[i])
	{
		if (is_quote(str[i]) && !current_quote)
		{
			current_quote = str[i];
			count++;
		}
		else if (str[i] == current_quote)
		{
			current_quote = '\0';
			count++;
		}
		i++;
	}
	return (count);
}

void	copy_without_quotes(char *out, char *str)
{
	int		i;
	int		j;
	char	current_quote;

	i = 0;
	j = 0;
	current_quote = '\0';
	while (str[i])
	{
		if (is_quote(str[i]) && !current_quote)
			current_quote = str[i];
		else if (str[i] == current_quote)
			current_quote = '\0';
		else
			out[j++] = str[i];
		i++;
	}
	out[j] = '\0';
}

char	*quote_cutter(char *str)
{
	char	*out;

	if(!str[0])
		return(ft_strdup(str));
	out = (char *)malloc((ft_strlen(str) - count_rm_quotes(str) + 1)
			* sizeof(char));
	if (!out)
		return (NULL);
	copy_without_quotes(out, str);
	return (free(str), out);
}
