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
		//freestrings(*input, promptline, NULL, NULL);  //whats going on here?
		(void) data;
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

	args = 0;
	argv = NULL;
	(void) env;
	promptline = prompt();
	while (1)
	{
		data = ft_calloc(sizeof(t_data), 1);
		if(!data)
			return(1);
		init_data(data, args, argv);
		if (!take_input(&input, promptline, data))
			return (1);
		free(promptline);
		if (ft_strlen(input) > 0)
			add_history(input);
		tokens = split_token(input);
		free(input);
		if(load_tokens(tokens, data))
			return(1);
		parse_tokens(data);
		//executer(data->execs, env);
		//ft_strlen (env[0]); //dont need
		free_data(data);
	}
	return (0);
}