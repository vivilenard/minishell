#include "../include/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_errno = 130;
}

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);
}

int	take_input(char **input, char *promptline)
{
	*input = readline(promptline);
	if (!*input)
		return (ft_putendl_fd("Shell Aborted", 2), 0);
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (1);
}

int	g_errno = 0;

int	main(int args, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	signals();
	data = init_data(env, args, argv);
	while (1)
	{
		reset_data(data);
		if (!take_input(&input, data->promptline))
			break ;
		lexer(input, data);
		if (!parse_tokens(data))
			break ;
		expander(data->execs, data->env);
		//print_execs(data);
		executer(data);
		//free_exec(data, input);
	}
	free_data(data);
	//system ("leaks shell");
	return (0);
}
