#include "../include/minishell.h"

//create a struct for filedescriptors

int	in_out(t_exec *exec)
{
	if (ft_strncmp(exec->input[0], "pipe", 5) != 0)
		file_as_stdin(exec);
	else if (ft_strncmp(exec->input[0], "pipe", 5) == 0)
		pipe_as_stdin();
	if (ft_strncmp(exec->output[0], "pipe", 5) != 0)
		file_as_stdout(exec);
	else if (ft_strncmp(exec->output[0], "pipe", 5) == 0)
		pipe_as_stdout();
	return (0);
}

int	create_child(t_exec *exec)
{
	in_out(exec);
	execve(exec->command, exec->args, NULL);		//which getenv?
	return (0);
}

int	executer(t_exec **exec)
{
	int	i;

	i = 0;
	while (1)
	{
		create_child(exec[i]);
		if (ft_strncmp(exec[i]->output[1], "pipe", 5) == 0)
			break;
		i++;
	}
	return (0);
}
	// printf("%s\n", exec->command);
	// printf("args: %s, %s\n", exec->args[0], exec->args[1]);