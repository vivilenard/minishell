#include "../include/minishell.h"


void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("" ,0);
	rl_redisplay();
}

int main (void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);

	char *input;
	char *promptline;

	promptline = prompt();
	while (1)
	{
		input = readline(promptline);
		if(!input)
			exit(1);
	}
	
	freestrings(input, promptline, NULL, NULL);
	return (0);
}