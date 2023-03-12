#include "../include/minishell.h"

char *username()
{
	return (getenv("USER"));
}

char *prompt()
{
	char	*user;
	char	*prompt;
	
	user = username();
	prompt = ft_strjoin(user, "@minishell\x1B[95m♥ \x1B[37m");
	return (prompt);
}
