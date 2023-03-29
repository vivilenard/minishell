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

void	handle_sigquit(int sig)
{
	(void) sig;
	exit(3);
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

int	create_child(t_exec *exec, t_data *data, int *fd_pipe, int fd_keep_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		rl_catch_signals = 0;
    	rl_clear_signals();
		signal(SIGQUIT, &handle_sigquit);
		if (in_out(exec, fd_pipe, fd_keep_pipe) == -1)
		{
			close_pipe(fd_pipe);
			exit (1);
		}
		close_pipe(fd_pipe);
		wrong_command(exec);
		built_in_child(exec, &data->env, data);
		if (execve(exec->command, exec->args, data->env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(exec->command, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit (127);
		}
	}
	if (close(fd_pipe[1]) == -1)
		perror ("close pipe[1]");
	if (fd_keep_pipe != 99 && close(fd_keep_pipe) == -1)
		perror ("close keep_pipe");
	return (fd_pipe[0]);
}

int	executer(t_data *data)
{
	int		i;
	int		fd_pipe[2];
	int		fd_keep_pipe;
	int		pid = 0;

	i = 0;
	fd_keep_pipe = 99;

	if(!data->execs[1] && is_specialbuiltin(data->execs[0]))
		built_in(data->execs[i], &data->env, data);
	else
	{
		while (data->execs[i])
		{
			if(pipe(fd_pipe) == -1)
				perror("create pipe");
			fd_keep_pipe = create_child(data->execs[i], data, fd_pipe, fd_keep_pipe);
			i++;
		}
		if (close(fd_keep_pipe) == -1)
			perror ("close keep_pipe");
		while (i >= 0)
		{
			waitpid(0, &pid, 0);
			i--;
		}
		error_codes(pid);
	}
	return (0);
}