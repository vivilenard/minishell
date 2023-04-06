#include "../include/minishell.h"

void	put_new_promptline(void)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	take_input(char **input, char *promptline)
{
	if (isatty(0))
		*input = readline(promptline);
	else
		*input = get_next_line(0);
	if (!*input)
		return (0);
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (1);
}

int	g_errno = 0;

int	main(int args, char **argv, char **env)
{
	t_data	*data;

	data = init_data(env, args, argv);
	while (1)
	{
		signals();
		reset_data(data);
		if (!take_input(&data->inputline, data->promptline))
			break ;
		if (ft_strncmp(data->inputline, "", 1) == 0)
			continue ;
		if (!lexer(data->inputline, data))
			continue ;
		if (!parse_tokens(data))
			continue ;
		if (!expander(data->execs, data->env, data))
			continue ;
		executer(data);
		free_exec(data, data->inputline);
	}
	free_data(data);
	return (g_errno);
}
