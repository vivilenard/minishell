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

	t_data	*data;

	args = 0;
	argv = NULL;
	data = ft_calloc(sizeof(t_data), 1);
	if(!data)
		return(free(data->promptline), exit(EXIT_FAILURE), 1);
	data->promptline = prompt();
	data->env = dupclicate_2D(env);
	while (1)
	{
		init_data(data, args, argv);
		if (!take_input(&input, data->promptline, data))
			return (free_data(data), EXIT_FAILURE);
		if (ft_strlen(input) > 0)
			add_history(input);
		if(load_tokens(lexer(input), data))
			return(free_data(data), EXIT_FAILURE);
		if(parse_tokens(data))
			return(free_data(data), EXIT_FAILURE);
		expander(data->execs, data->env);
		executer(data);
		free_exec(data);
	}
	free_exec(data);
	free_data(data);
	return (0);
}