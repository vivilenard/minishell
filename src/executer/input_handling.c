#include "../../include/minishell.h"

int	open_infile(t_exec *exec, int *fd, int i)
{
	if (ft_strncmp(exec->input[i], "<", 2) == 0 || ft_strncmp(exec->input[i], "< ", 3) == 0)
	{
		*fd = open (exec->input[i + 1], O_RDONLY);
		if (*fd == -1)
		{
			perror("open inputfile");
			g_errno = 1;
			return (-1);
		}
		if (dup2(*fd, 0) == -1)
			return (perror("file as stdin"), -1);
		close(*fd);
	}
	return (0);
}


void	heredoc_as_in(t_exec *exec, int *fd_pipe, int i)
{
	if (ft_strncmp(exec->input[i - 2], "<<", 3) == 0)
		pipe_as_stdin(fd_pipe[0]);
	if (close(fd_pipe[1]) == -1)
		perror("close pipe as stdin");
}

int	init_heredoc_pipe(t_exec *exec, int *fd)
{
	int	i;

	i = 0;
	while (exec->input[i])
	{
		if (ft_strncmp(exec->input[i], "<<", 3) == 0)
		{
			if (pipe(fd) == -1)
				return (perror("open heredoc pipe"), -1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	heredoc(t_exec *exec, int *fd, int i)
{
	char	*line;

	if (ft_strncmp(exec->input[i], "<<", 3) == 0)
	{
		while (1)
		{
			ft_putstr_fd("heredoc>", 1);
			line = get_next_line(0);
			if (!line)
				return (perror("gets no line"), 0);
			if (ft_strncmp(exec->input[i + 1], line, ft_strlen(exec->input[i + 1])) == 0
				&& ft_strlen(line) == ft_strlen(exec->input[i + 1]) + 1)
			{
				free (line);
				break ;
			}
			if (write(fd[1], line, ft_strlen(line)) == -1)
				perror("write to here_doc.txt");
			free (line);
		}
	}
	return (0);
}


// int	heredoc(t_exec *exec, int *fd, int i)
// {
// 	if (ft_strncmp(exec->input[i], "<<", 3) == 0)
// 	{
		// if (pipe(fd) == -1)
		// 	return (perror("open heredoc pipe"), -1);
		//write_heredoc(exec, fd, i);
		// close(fd[1]);
		// pipe_as_stdin(fd[0]);
// 	}
// 	return (0);
// }
