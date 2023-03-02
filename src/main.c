#include "../include/minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main (int args, char **argv, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);

	char *input;
	char *promptline;
	char **tokens;

	t_data	*data;

	args = 0;
	argv = NULL;
	data = malloc(sizeof(t_data));
	if(!data)
		return(1);
	init_data(data);
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
		parse_tokens(data);
		printtokens(data->execs);
		/* print_execs(data); */
		executer(data->execs, env);
		/* free_exec(data); */
	}
	freestrings(input, promptline, NULL, NULL);
	return (0);
}