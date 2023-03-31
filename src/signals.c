#include "../include/minishell.h"

static void	disable_echo(void)
{
	struct termios	settings;

	tcgetattr(STDIN_FILENO, &settings);
	settings.c_lflag &= ~(IEXTEN | ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void	signals(void)
{
	disable_echo();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint);
}

void	signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	handle_sigint(int sig)
{
	(void)sig;
	put_new_promptline();
	g_errno = 1;
}
