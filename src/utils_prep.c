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
	prompt = ft_strjoinwithoutfree(user, "@minishell♥ ");
	return (prompt);
}
