#include "../../include/minishell.h"

int	in_out(t_exec *exec, int *fd_pipe, int fd_keep_pipe)
{
	if (ft_strlen(exec->input[0]) > 0
		&& ft_strncmp(exec->input[0], "|", 2) != 0)
	{
		ft_putendl_fd("file as stdin", 2);
		file_as_stdin(exec);
	}
	else if (ft_strlen(exec->input[0]) > 0
		&& ft_strncmp(exec->input[0], "|", 2) == 0)
	{
		ft_putendl_fd("pipe as stdin", 2);
		pipe_as_stdin(fd_keep_pipe);
	}
	if (ft_strlen(exec->output[0]) > 0
		&& ft_strncmp(exec->output[0], "|", 2) != 0)
	{
		ft_putendl_fd("file as stdout", 2);
		file_as_stdout(exec);
	}
	if (ft_strlen(exec->output[0]) > 0
		&& ft_strncmp(exec->output[0], "|", 2) == 0)
	{
		ft_putendl_fd("pipe as stdout", 2);
		pipe_as_stdout(fd_pipe);
	}
	close_pipe(fd_pipe);
	return (0);
}

int	heredoc(t_exec *exec)
{
	int		fd[2];
	char	*line;

	ft_putendl_fd("I am heredoc", 2);
	//fd = open ("heredoc", O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (pipe(fd) == -1)
		return (perror("open heredoc pipe"), -1);
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		line = get_next_line(0);
		if (!line)
		{
			perror("gets no line");
			return (0);
		}
		if (ft_strncmp(exec->input[1], line, ft_strlen(exec->input[1])) == 0
			&& ft_strlen(line) == ft_strlen(exec->input[1]) + 1)
		{
			free(line);
			return (0);
		}
		if (write(fd[1], line, ft_strlen(line)) == -1)
			perror("write to here_doc.txt");
		free (line);
	}
	close(fd[1]);
	pipe_as_stdin(fd[0]);
	return (fd[0]);
}

int	file_as_stdin(t_exec *exec)
{
	int	fd;

	if (ft_strncmp(exec->input[0], "<<", 3) == 0)
		fd = heredoc(exec);
	else
	{
		fd = open (exec->input[1], O_RDONLY);
		if (fd == -1)
			perror("open inputfile");
		if (dup2(fd, 0) == -1)
			perror("file as stdin");
	}
	close(fd);
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
	close(fd_keep_pipe);
	return (0);
}

int	pipe_as_stdout(int *fd_pipe)
{
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		perror("pipe as stout");
	return (0);
}
