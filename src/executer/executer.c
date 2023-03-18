#include "../../include/minishell.h"

int	error_codes(int	err)
{
	if (WIFEXITED(err))
	{
		err = WEXITSTATUS(err);
		if (err == 1)
			g_errno = 1;
		if (err == 2)
			g_errno = 127;
		if (err == 3)
			g_errno = 3;
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

int	create_child(t_exec *exec, t_data *data, int *fd_pipe, int fd_keep_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, handle_sigquit);
		if (in_out(exec, fd_pipe, fd_keep_pipe) == -1)
			exit (1);
		if (built_in(exec, data->env, data))
			exit (0);
		if (execve(exec->command, exec->args, data->env) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(exec->command, 2);
			ft_putstr_fd(": command not found\n", 2);
			exit (2);
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
	int		err = 0;

	i = 0;
	fd_keep_pipe = 99;

	if(is_childless_built_in(data->execs[i]->command))
		built_in(data->execs[i], data->env, data);
	else
	{
		while (data->execs[i])
		{
			if(pipe(fd_pipe) == -1)
				perror("create pipe");
			usleep (3000);  //actually dont need if executer is perfect
			fd_keep_pipe = create_child(data->execs[i], data, fd_pipe, fd_keep_pipe);
			i++;
		}
		if (close(fd_keep_pipe) == -1)
			perror ("close keep_pipe");
		while (i >= 0)
		{
			waitpid(0, &err, 0);
			i--;
		}
	}
	error_codes(err);
	return (0);
}
