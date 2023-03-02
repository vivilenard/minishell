#include "../include/minishell.h"

void	ftenv(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	pwd()
{

}

int	built_in(t_exec *exec, char **env)
{
	ft_strlen(env[0]);
	ft_strlen(exec->input[0]);
	// if (ft_strncmp(exec->command, "echo", 5) == 0)
	// 	echo(exec->args);
	// else if (ft_strncmp(exec->command, "cd", 3) == 0)
	// 	cd(exec->args);
	// if (ft_strncmp(exec->command, "pwd", 4) == 0)
	// 	pwd(exec->args);
	// else if (ft_strncmp(exec->command, "export", 7) == 0)
	// 	export(exec->args);
	// else if (ft_strncmp(exec->command, "unset", 6) == 0)
	// 	unset(exec->args);
	if (ft_strncmp(exec->command, "env", 4) == 0)
		ftenv(exec->args);
	// else if (ft_strncmp(exec->command, "exit", 5) == 0)
	// 	ftexit(exec->args);
	return (0);
}
