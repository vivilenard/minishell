#include "../include/minishell.h"

int	numberoftokens(char *input)
{
	return (ft_strlen(input) + 1);	
}

t_token	*allocatetokens(char *input)
{
	t_token *tokens;

	tokens = malloc(sizeof(t_token) * numberoftokens(input));
	return (tokens);
}

t_token *lexer(char *input)
{
	t_token *tokens;

	tokens = allocatetokens(input);
	return (tokens);
}