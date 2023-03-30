#include "../../include/minishell.h"

int	error_codes(int	pid)
{
	int err;

	err = 0;
	if (WIFEXITED(pid))
	{
		err = WEXITSTATUS(pid);
		g_errno = err;
	}
	return (0);
}

void	close_pipe(int *fd_pipe)
{
	if (fd_pipe[0])
	{
		if (close(fd_pipe[0]) == -1)
			perror("close fd_pipe[0]");
		if (close(fd_pipe[1]) == -1)
			perror("close fd_pipe[1]");
	}
}

void	wrong_command(t_exec *exec)
{
	if (!exec->command || !exec->command[0])
		exit(0);
	if (exec->args[0] && ft_strncmp(exec->args[0], ".", 2) == 0)
	{
		ft_putendl_fd("minishell: .: filename argument required", 2);
		ft_putendl_fd(".: usage: . filename [arguments]", 2);
		exit(2);
	}
	if (exec->args[0] && ft_strncmp(exec->args[0], "..", 2) == 0)
	{
		ft_putendl_fd("minishell: ..: filename argument required", 2);
		ft_putendl_fd("..: usage: .. filename [arguments]", 2);
		exit(2);
	}
}

void	handle_sigquit(int sig)
{
	(void) sig;
	exit(3);
}

void signals_child(void)
{
	rl_catch_signals = 0;
	rl_clear_signals();
	signal(SIGQUIT, &handle_sigquit);
}