#include "../../include/minishell.h"

char	*ft_strjoin_free_opt(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*str;
	size_t	i;
	size_t	len;
	size_t	n;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	n = 0;
	while (s2 && s2[n] != '\0')
	{
		str[i] = s2[n];
		i++;
		n++;
	}
	str[len - 1] = '\0';
	if (free_s1 && s1 != NULL)
		free (s1);
	if (free_s2 && s2 != NULL)
		free (s2);
	return (str);
}


char *last_occurence(char *str, char c)
{
	char *p;
	int	i;

	i = ft_strlen(str);
	p = str;
	while(p[i] != c)
		i--;
	return(&p[i]);
}

char *string_split(char *str, char c, int at_first, int first)
{
    // splits string at first or last occurrence of a char and returns
    // either first or last part of the string.

    char *out;
	char *p;
    int len;

	len = 0;
    if (!str || !c)
		return NULL;
    while (str[len] && str[len] != c)
        len++;
    if (!at_first) // find the last occurrence of the delimiter
	{
        p = last_occurence(str, c);
        if (p)
            len = p - str;
    }
    if (first)
	{
        out = (char *) malloc(sizeof(char) * (len + 1));
        if (!out)
            return (NULL);
        ft_strlcpy(out, str, len+1);
        out[len] = '\0';
    }
	else
	{
        out = (char *) malloc(sizeof(char) * (ft_strlen(str) - len + 1));
        if (!out)
        	return NULL;
        ft_strlcpy(out, str + len + 1, ft_strlen(str) - len);
        out[ft_strlen(str) - len - 1] = '\0';
    }
    return (out);
}