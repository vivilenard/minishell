#include "../../include/minishell.h"

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
	char *cwd;

	cwd = getcwd(NULL, 1024);

	//ft_printf("%s\n", cwd);
	ft_putendl_fd(cwd, 2);
	free(cwd);
}

int	built_in(t_exec *exec, char **env)
{
	ft_strlen(env[0]);
	ft_strlen(exec->input[0]);
	// if (ft_strncmp(exec->command, "echo", 5) == 0)
	// 	echo(exec->args);
	// else if (ft_strncmp(exec->command, "cd", 3) == 0)
	// 	cd(exec->args);
	if (ft_strncmp(exec->command, "/bin/pwd", 9) == 0)
	 	pwd();
	// else if (ft_strncmp(exec->command, "export", 7) == 0)
	// 	export(exec->args);
	// else if (ft_strncmp(exec->command, "unset", 6) == 0)
	// 	unset(exec->args);
	//printf("%s\n", exec->command);
	if (ft_strncmp(exec->args[0], "env", 4) == 0)
		ftenv(env);
	// else if (ft_strncmp(exec->command, "exit", 5) == 0)
	// 	ftexit(exec->args);
	return (0);
}
