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

int	assigntokens(t_token *tokens)
{
	return (0);
}

t_token *lexer(char *input)
{
	t_token *tokens;

	tokens = allocatetokens(input);
	while (1)
	{
		//take a token and assign an enum, do it until error or endofstring
		if (assigntokens(tokens) == 0)
		break;
	}
	//printf("%s\n", tokens[4].content);
	return (tokens);
}