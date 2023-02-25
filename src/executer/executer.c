#include "../include/minishell.h"

//create a struct for filedescriptors

void	close_pipe(int	*fd_pipe)
{
	ft_putendl_fd("close pipe ", 2);
	//printf("%d\n", fd_pipe[0]);
	ft_putnbr_fd(fd_pipe[0], 2);
	ft_putnbr_fd(fd_pipe[1], 2);
	ft_putendl_fd(" ", 2);
	if (fd_pipe[0])
	{
	if (close(fd_pipe[0]) == -1)
		perror("close fd_pipe[0]");
	if (close(fd_pipe[1]) == -1)
		perror("close fd_pipe[1]");
	}
}

int	file_as_stdin(t_exec *exec)
{
	int	fd;

	fd = open (exec->input[1], O_RDONLY);
	if (fd == -1)
		perror("open inputfile");
	if (dup2(fd, 0) == -1)
		perror("file as stdin");
	return (close(fd), 0);
}

int	file_as_stdout(t_exec *exec)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(exec->output[0], ">>", 3) == 0)
		fd = open (exec->output[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if(ft_strncmp(exec->output[0], ">", 2) == 0)
		fd = open (exec->output[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		perror("open outputfile");
	if (dup2(fd, 1) == -1)
		perror ("file as stdout");
	return (0);
}

// int	pipe_as_stdin(int *fd_pipe)
// {
// 	if (dup2(fd_pipe[0], 0) == -1)
// 		perror("pipe as stdin");
// 	return (0);
// }

int	pipe_as_stdout(int *fd_pipe)
{
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		perror("pipe as stout");
	if (dup2(fd_pipe[0], STDIN_FILENO) == -1)
		perror("pipe as stdin");
	return (0);
}

int	in_out(t_exec *exec, int *fd_pipe)
{
	if (ft_strncmp(exec->input[0], "pipe", 5) != 0)
	{
		ft_putendl_fd("file as stdin\n", 2);
		file_as_stdin(exec);
	}
	else if (ft_strncmp(exec->input[0], "pipe", 5) == 0)
	{
		ft_putendl_fd("pipe as stdin", 2);
		//pipe_as_stdin(fd_pipe);
	}
	if (ft_strncmp(exec->output[0], "pipe", 5) != 0)
	{
		ft_putendl_fd("file as stdout\n", 2);
		file_as_stdout(exec);
	}
	else if (ft_strncmp(exec->output[0], "pipe", 5) == 0)
	{
		ft_putendl_fd("pipe as stdout\n", 2);
		pipe_as_stdout(fd_pipe);
	}
	close_pipe(fd_pipe);
	return (0);
}

int	create_child(t_exec *exec)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		printf("llala\n");
		if (execve(exec->command, exec->args, NULL) == -1)		//which getenv?
			perror("execve");
	}
	return (0);
}

int	executer(t_exec **exec)
{
	int	i;
	int	fd_pipe[2];
	//int	fd_oldpipe[2];

	printf("%s\n", exec[0]->command);
	printf("%s\n", exec[0]->args[0]);
	printf("%s\n", exec[0]->args[1]);
	printf("%s\n", exec[0]->input[0]);
	printf("%s\n", exec[0]->input[1]);
	printf("%s\n", exec[0]->output[0]);
	printf("%s\n", exec[0]->output[1]);
	printf("%s\n", exec[1]->command);
	printf("%s\n", exec[1]->args[0]);
	printf("%s\n", exec[1]->args[1]);
	printf("%s\n", exec[1]->input[0]);
	printf("%s\n", exec[1]->output[1]);
	printf("\n\nEXECUTER\n\n");
	i = 0;
	while (exec[i])
	{
		ft_putendl_fd("Executing !", 2);
		if (pipe(fd_pipe) == -1)
			perror("create pipe");
		in_out(exec[i], fd_pipe);
		ft_putendl_fd("bef fork", 2);
		create_child(exec[i]);
		usleep(10);
		if (ft_strncmp(exec[i]->output[1], "pipe", 5) == 0)
		 	break;
		i++;
	}
	//waitpid(0, NULL, 0);
	return (0);
}
	// printf("%s\n", exec->command);
	// printf("args: %s, %s\n", exec->args[0], exec->args[1]);