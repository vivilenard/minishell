#include "../../include/minishell.h"

int	in_out(t_exec *exec, int *fd_pipe, int fd_keep_pipe)
{
	int	err;

	err = 0;
	if (ft_strlen(exec->input[0]) > 0
		&& ft_strncmp(exec->input[0], "|", 2) != 0)
		err = file_as_stdin(exec);
	else if (ft_strlen(exec->input[0]) > 0
		&& ft_strncmp(exec->input[0], "|", 2) == 0)
		err = pipe_as_stdin(fd_keep_pipe);
	if (ft_strlen(exec->output[0]) > 0
		&& ft_strncmp(exec->output[0], "|", 2) != 0)
		err = file_as_stdout(exec);
	if (ft_strlen(exec->output[0]) > 0
		&& ft_strncmp(exec->output[0], "|", 2) == 0)
		err = pipe_as_stdout(fd_pipe);
	if (err == -1)
		close_pipe(fd_pipe);
	return (err);
}

int	file_as_stdin(t_exec *exec)
{
	int	i;
	int	fd_pipe[2];
	int	fd_file;
	int	here_doc;

	i = 0;
	fd_file = 0;
	here_doc = init_heredoc_pipe(exec, fd_pipe);
	while (exec->input[i])
	{
		if (open_infile(exec, &fd_file, i) == -1)
			return (-1);
		else if (heredoc(exec, fd_pipe, i) == -1)
			return (-1);
		i = i + 2;
	}
	if (here_doc == 1)
		heredoc_as_in(exec, fd_pipe, i);
	return (0);
}

int	file_as_stdout(t_exec *exec)
{
	int	fd;
	int	i;

	fd = -1;
	i = 0;
	while (exec->output[i])
	{
		if (ft_strncmp(exec->output[i], ">>", 3) == 0)
			fd = open (exec->output[i + 1], O_CREAT
					| O_APPEND | O_WRONLY, 0644);
		else if (ft_strncmp(exec->output[i], ">", 2) == 0)
			fd = open (exec->output[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		i = i + 2;
	}
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
