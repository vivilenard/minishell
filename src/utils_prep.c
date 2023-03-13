#include "../include/minishell.h"

char *username()
{
	return (getenv("USER"));
}

char *prompt(t_data *data)
{
	char	*user;
	char	*prompt;
	char	*pwd;
	char	*tmp;
	
	(void) data;
	user = username();
	tmp = getcwd(NULL, 1024);
	pwd = NULL;
	pwd = string_split(tmp, '/', 0, 0);
	free(tmp);
	prompt = ft_strjoin(user, "@minishell\x1B[95m♥ \x1B[37m");
	tmp = ft_strjoin_free_opt(pwd,"/ ", 1, 0);
	prompt = ft_strjoin_free_opt(prompt, tmp, 1, 1);
	return (prompt);
}
