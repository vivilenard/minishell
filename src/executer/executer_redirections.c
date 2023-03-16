#include "../../include/minishell.h"

int	in_out(t_exec *exec, int *fd_pipe, int fd_keep_pipe)
{
	int	err;

	err = 0;
	if (ft_strlen(exec->input[0]) > 0
		&& ft_strncmp(exec->input[0], "|", 2) != 0)
	{
		//ft_putendl_fd("file as stdin", 2);
		err = file_as_stdin(exec);
	}
	else if (ft_strlen(exec->input[0]) > 0
		&& ft_strncmp(exec->input[0], "|", 2) == 0)
	{
		//ft_putendl_fd("pipe as stdin", 2);
		err = pipe_as_stdin(fd_keep_pipe);
	}
	if (ft_strlen(exec->output[0]) > 0
		&& ft_strncmp(exec->output[0], "|", 2) != 0)
	{
		//ft_putendl_fd("file as stdout", 2);
		err = file_as_stdout(exec);
	}
	if (ft_strlen(exec->output[0]) > 0
		&& ft_strncmp(exec->output[0], "|", 2) == 0)
	{
		//ft_putendl_fd("pipe as stdout", 2);
		err = pipe_as_stdout(fd_pipe);
	}
	close_pipe(fd_pipe);
	return (err);
}

int	file_as_stdin(t_exec *exec)
{
	int	fd;

	if (ft_strncmp(exec->input[0], "<<", 3) == 0)
		heredoc(exec);
	else
	{
		fd = open (exec->input[1], O_RDONLY);
		if (fd == -1)
		{
			perror("open inputfile");
			errno = 1;
			return (-1);
		}
		if (dup2(fd, 0) == -1)
		{
			perror("file as stdin");
			return (-1);
		}
		close(fd);
	}
	return (0);
}

int	file_as_stdout(t_exec *exec)
{
	int	fd;

	fd = -1;
	if (ft_strncmp(exec->output[0], ">>", 3) == 0)
		fd = open (exec->output[1], O_CREAT | O_APPEND | O_WRONLY, 0644);
	else if (ft_strncmp(exec->output[0], ">", 2) == 0)
		fd = open (exec->output[1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		perror("open outputfile");
	if (dup2(fd, 1) == -1)
		perror ("file as stdout");
	return (0);
}

int	pipe_as_stdin(int fd_keep_pipe)
{
	if (dup2(fd_keep_pipe, 0) == -1)
		perror("pipe as stdin");
	if (close(fd_keep_pipe) == -1)
		perror("close pipe as stdin");
	return (0);
}

int	pipe_as_stdout(int *fd_pipe)
{
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		perror("pipe as stout");
	return (0);
}
