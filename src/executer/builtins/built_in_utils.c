#include "../../../include/minishell.h"

int	char_is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_s_e(char **args, int start, int end, char *c)
{
	int		i;
	char	*out;

	i = start;
	if (!args || !*args)
		return (NULL);
	if (i == end && args[i])
		return (args[i]);
	out = ft_calloc(sizeof(char), 1);
	while (i <= end && args[i])
	{
		out = ft_strjoin_free_opt(out, args[i], 1, 0);
		if (args[i + 1] && i < end)
			out = ft_strjoin_free_opt(out, c, 1, 0);
		i++;
	}
	return (out);
}

char	*last_occurence(char *str, char c)
{
	char	*p;
	int		i;

	i = ft_strlen(str);
	p = str;
	while (p[i] != c)
		i--;
	return (&p[i]);
}

char	*split_first(char *out, char *str, int len)
{
	out = (char *) malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, str, len + 1);
	out[len] = '\0';
	return (out);
}

char	*split_second(char *out, char *str, int len)
{
	out = (char *) malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, str + len + 1, ft_strlen(str) - len);
	out[ft_strlen(str) - len - 1] = '\0';
	return (out);
}

char	*string_split(char *str, char c, int at_first, int first)
{
	char	*out;
	char	*p;
	int		len;

	len = 0;
	out = NULL;
	if (!str || !c)
		return (NULL);
	if (!char_is_in_str(str, c))
		return (str);
	while (str[len] && str[len] != c)
		len++;
	if (!at_first)
	{
		p = last_occurence(str, c);
		if (p)
			len = p - str;
	}
	if (first)
		out = split_first(out, str, len);
	else
		out = split_second(out, str, len);
	return (out);
}

int	is_specialbuiltin(t_exec *exec)
{
	if (exec->command && (ft_strncmp(exec->command, "cd", 3) == 0
			|| ft_strncmp(exec->command, "exit", 5) == 0
			|| ft_strncmp(exec->command, "export", 7) == 0
			|| ft_strncmp(exec->command, "expand", 7) == 0
			|| ft_strncmp(exec->command, "unset", 6) == 0))
		return (1);
	return (0);
}

void	is_only_dollarsign(char **str)
{
	int		i;
	char	*s;

	s = *str;
	i = 0;
	while (s[i])
	{
		if (s[i] != '$')
			return ;
		i++;
	}
	free(s);
	*str = ft_strdup("$");
}
