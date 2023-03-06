#include "../../include/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	ft_pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 1024);
	ft_printf("%s\n", cwd);
	free(cwd);
}

char *trim_last(char *str, char c)
{
	int		i;
	char	*new;

	i = ft_strlen(str);
	while(str[i] != c)
		i--;
	new = ft_calloc(sizeof(char), i + 1);
	if(!new)
		return(NULL);
	ft_strlcpy(new, str, i + 1);
	return(new);
}

char	*analyse_path(char *path)
{
	int	i;
	int counter;

	counter = 0;
	i = 0;
	while(path[i])
	{
		while(path[i] == '.')
			i++;
		if(path[i] == '/')
		{
			counter++;
			i++;
		}
	}
	i = 0;
	while(i < counter)
	{
		trim_last(path, '/');
		counter--;
	}
	return(path);
}

void ft_cd(t_exec *exec, char **env)
{
	char	*path;
	char	*temp;
	int		i;


	i = 0;
	//(void) env;
	path = exec->args[1]; 
	ft_printf("CURRENT PWD:%s\n", getcwd(NULL, 1024));
	ft_printf("CD TO:%s\n", path);
	if (chdir(path) == -1)
		return ;
	ft_printf("NEW PWD:%s\n", getcwd(NULL, 1024));
	while(env[i])
	{
		if(ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			temp = getcwd(NULL, 1024);
			env[i] = ft_strjoin("PWD=", temp);
			free(temp);
			ft_printf("NEW PWD after copy:%s\n", env[i]);
		}
		i++;
	}
}

int	built_in(t_exec *exec, char **env)
{
	// if (ft_strncmp(exec->command, "echo", 5) == 0)
	// 	echo(exec->args);
	if (ft_strncmp(exec->command, "cd", 3) == 0)
		ft_cd(exec, env);
	if (ft_strncmp(exec->command, "pwd", 4) == 0)
	{
	 	ft_pwd();
		exit(EXIT_SUCCESS);
	}
	// else if (ft_strncmp(exec->command, "export", 7) == 0)
	// 	export(exec->args);
	// else if (ft_strncmp(exec->command, "unset", 6) == 0)
	// 	unset(exec->args);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
	{
		ft_env(env);
		exit(EXIT_SUCCESS);
	}
	// else if (ft_strncmp(exec->command, "exit", 5) == 0)
	// 	ftexit(exec->args);
	return (0);
}
