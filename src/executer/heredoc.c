#include "../../include/minishell.h"

int	heredoc(t_exec *exec)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		return (perror("open heredoc pipe"), -1);
	while (1)
	{
		ft_putstr_fd("heredoc>", 1);
		line = get_next_line(0);
		if (!line)
			return (perror("gets no line"), 0);
		if (ft_strncmp(exec->input[1], line, ft_strlen(exec->input[1])) == 0
			&& ft_strlen(line) == ft_strlen(exec->input[1]) + 1)
		{
			free (line);
			break ;
		}
		if (write(fd[1], line, ft_strlen(line)) == -1)
			perror("write to here_doc.txt");
		free (line);
	}
	close(fd[1]);
	pipe_as_stdin(fd[0]);
	return (0);
}
