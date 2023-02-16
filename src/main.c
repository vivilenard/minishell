#include "../include/minishell.h"

	//enum token{word = 1, option, pipe, io};
int main ()
{
	char *input;
	char *promptline;
	t_token *tokens;

	promptline = prompt();
	input = readline(promptline);
	tokens = lexer(input);
	freestrings(input, promptline, NULL, NULL);
	//system ("leaks shell");
	return (0);
}