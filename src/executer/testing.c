#include "../../include/minishell.h"
#include <string.h>

/* char *string_split(char *str, char c, int at_first, int first)
{
	//splits string at first or last occurence of a char and returns
	//either first or last part of the string.

	int		len;
	char	*out;
	int		i;

	if(!str)
		return(NULL);
	if(!c)
		return(str);

	i = 0;
	len = 0;
	if(at_first) //at first occurence
		while(str[len] && str[len] != c)
			len++;
	else //at last occurence
	{
		len = strlen(str);
		while(str[len] != c)
			len--;
	}
	if(first) // returning 1st part 
	{
		out = (char *) malloc(sizeof(char) * (len + 1));
		if(!out)
			return (NULL);
		while(i < len && str[i])
		{
			out[i] = str[i];
			i++;
		}
	}
	else	//return 2nd part
	{
		out = (char *) malloc(sizeof(char) * (strlen(str) - len + 1));
		if(!out)
			return (NULL);
		while(i <= len && str[len + i])
		{
			out[i] = str[len + i];
			i++;
		}
	}
	return(out);
} */

/* char *string_split(char *str, char c, int at_first, int first)
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
        p = strrchr(str, c);
        if (p)
            len = p - str;
    }
    if (first)
	{
        out = (char *) malloc(sizeof(char) * (len + 1));
        if (!out)
            return NULL;
        strncpy(out, str, len);
        out[len] = '\0';
    }
	else
	{
        out = (char *) malloc(sizeof(char) * (strlen(str) - len));
        if (!out)
        	return NULL;
        strncpy(out, str + len + 1, strlen(str) - len - 1);
        out[strlen(str) - len - 1] = '\0';
    }
    return (out);
} */

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
        ft_strlcpy(out, str, len);
        out[len] = '\0';
    }
	else
	{
        out = (char *) malloc(sizeof(char) * (ft_strlen(str) - len));
        if (!out)
        	return NULL;
        ft_strlcpy(out, str + len + 1, ft_strlen(str) - len - 1);
        out[ft_strlen(str) - len - 1] = '\0';
    }
    return (out);
}

int main(void)
{
	
	printf("First Part until first Occurence: %s\n", string_split("Test==Value", '=', 1, 1));
	printf("First Part until last Occurence: %s\n", string_split("Test==Value", '=', 0, 1));
	printf("Second Part until first Occurence: %s\n", string_split("Test==Value", '=', 1, 0));
	printf("Second Part until last Occurence: %s\n", string_split("Test==Value", '=', 0, 0));

	return(0);
}