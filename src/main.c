#include "../include/minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main (void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);

	char *input;
	char *promptline;
	char **tokens;

	t_data	*data;

	data = malloc(sizeof(*data));
	if(!data)
		return(1);
	data->tokens = malloc(sizeof(**tokens));
/* 	if(data->tokens)
		return(1); */
	//init_data(data);
	promptline = prompt();
	while (1)
	{
		input = readline(promptline);
		if(!input)
		{
			ft_putendl_fd("Shell Aborted", 2);
			freestrings(input, promptline, NULL, NULL);
			free_data(data);
		}
		if (ft_strlen(input) > 0)
			add_history(input);
		tokens = split_token(input);
		if(load_tokens(tokens, data))
			return(freestrings(input, promptline, NULL, NULL),
				free(tokens), free_data(data), 1);
	}
	freestrings(input, promptline, NULL, NULL);
	free_data(data);
	return (0);
}