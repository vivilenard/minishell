#include "../include/minishell.h"

void freestrings(char *s1, char *s2, char *s3, char **array)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (array)
		ft_free2d(array);
}

int is_char(char place, char c)
{
	if (place == c)
		return (1);
	return (0);
}

void switch_flag(int *flag)
{
	if (*flag == 0)
		*flag = 1;
	else if (*flag == 1)
		*flag = 0;
}