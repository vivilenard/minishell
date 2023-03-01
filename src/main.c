#include "../include/minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	take_input(char **input, char *promptline, t_data *data)
{
	*input = readline(promptline);
	if(!*input)
	{
		ft_putendl_fd("Shell Aborted", 2);
		freestrings(*input, promptline, NULL, NULL);
		free_data(data);
		return (0);
	}
	return (1);
}
int main (int args, char **argv, char **env)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);

	char *input;
	char *promptline;
	char **tokens;

	t_data	*data;

	input = NULL;
	data = malloc(sizeof(*data));
	if(!data)
		return(1);
	init_data(data, args, argv);
	promptline = prompt();
	while (1)
	{
		printf("\nSTART\n");
		if (!take_input(&input, promptline, data))
			return (0);
		if (ft_strlen(input) > 0)
			add_history(input);
		printf("\nLEXER\n");
		tokens = split_token(input);
		//ft_put2dstr_fd(tokens, 2);
		printf("load tokens\n");
		if(load_tokens(tokens, data))
			return(freestrings(input, promptline, NULL, NULL),
				free(tokens), free_data(data), 1);
		printf("\nPARSER\n");
		parse_tokens(data);
		//print_execs(data);
		//printtokens(data->execs);
		printf("\nEXECUTER\n");
		executer(data->execs, env);
	}
	freestrings(input, promptline, NULL, NULL);
	return (0);
}