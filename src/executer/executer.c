#include "../../include/minishell.h"

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

int	create_child(t_exec *exec, t_data *data, int *fd_pipe, int fd_keep_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		in_out(exec, fd_pipe, fd_keep_pipe);
		if (built_in(exec, data->env, data))
			exit (0);
		if (execve(exec->command, exec->args, data->env) == -1)
			perror("execve");
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
			//printf("%d\n", i);
			waitpid(0, NULL, 0);
			i--;
		}
	}
	return (0);
}
