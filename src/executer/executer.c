#include "../include/minishell.h"

//create a struct for filedescriptors

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

int	in_out(t_exec *exec, int *fd_pipe, int fd_keep_pipe)
{
	if (ft_strncmp(exec->input[0], "pipe", 5)
		!= 0 && ft_strlen(exec->input[0]) > 0)
	{
		ft_putendl_fd("file as stdin", 2);
		file_as_stdin(exec);
	}
	else if (ft_strncmp(exec->input[0], "pipe", 5) == 0)
	{
		ft_putendl_fd("pipe as stdin", 2);
		pipe_as_stdin(fd_keep_pipe);
	}
	if (ft_strncmp(exec->output[0], "pipe", 5) != 0)
	{
		ft_putendl_fd("file as stdout", 2);
		file_as_stdout(exec);
	}
	else if (ft_strncmp(exec->output[0], "pipe", 5) == 0)
	{
		ft_putendl_fd("pipe as stdout", 2);
		pipe_as_stdout(fd_pipe);
	}
	close_pipe(fd_pipe);
	return (0);
}

int	create_child(t_exec *exec, char **env, int *fd_pipe, int fd_keep_pipe)
{
	pid_t	pid;

	env = NULL;
	pid = fork();
	if (pid == 0)
	{
		in_out(exec, fd_pipe, fd_keep_pipe);
		if (execve(exec->command, exec->args, env) == -1)
			perror("execve");
	}
	if (close(fd_pipe[1]) == -1)
		perror ("close pipe[1]");
	if (fd_keep_pipe != 99 && close(fd_keep_pipe) == -1)
		perror ("close keep_pipe");
	return (fd_pipe[0]);
}

int	executer(t_exec **exec, char **env)
{
	int		i;
	int		fd_pipe[2];
	int		fd_keep_pipe;

	i = 0;
	fd_keep_pipe = 99;

	int n = 0;
	while (env[n])
	{
		printf("%s\n", env[n]);
		n++;
	}
	while (exec[i])
	{
		ft_putendl_fd("\nExecuting !\n", 2);
		if (pipe(fd_pipe) == -1)
			perror("create pipe");
		fd_keep_pipe = create_child(exec[i], env, fd_pipe, fd_keep_pipe);
		usleep(10000);
		if (ft_strncmp(exec[i]->output[1], "pipe", 5) == 0)
			break ;
		i++;
	}
	close(fd_keep_pipe);
	while (--i >= 0)
	{
		//printf("%d\n", i);
		waitpid(0, NULL, 0);
	}
	return (0);
}
