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

char **add_to_env(char *str, char **env)
{
	char **new_env;
	int	i;

	i = 0;
	if(!env || !*env)
		return(NULL);
	new_env = (char **) ft_calloc(sizeof(char *), ft_2darraylen(env) + 1);
	if (!new_env)
		return (ft_printf("Error ALLOC AddToEnv\n"), NULL);
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if(!new_env[i])
			return(NULL);
		i++;
	}
	new_env[i] = str;
	new_env[i +1] = NULL;
	ft_free2d(env);
	return(new_env);
}

char **replace_in_env(char *category, char *new_entry, char **env)
{
	int		i;

	i = 0;
	if(!env || !*env)
		return(NULL);
	while(env[i])
	{
		if(ft_strncmp(env[i], category, ft_strlen(category)) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin(category, new_entry);
		}
		i++;
	}
	return(env);
}

int category_is_in_env(char *category, char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if(ft_strncmp(env[i], category, ft_strlen(category)) == 0)
			return(1);
		i++;
	}
	return(0);
}

char	**remove_from_env(char *category, char **env)
{
	char	**new_env;
	int		i;
	int		j;
	int		category_len;

	i = 0;
	j = 0;
	printf("2dArraylen: %i\n", ft_2darraylen(env));
	new_env = malloc(sizeof(char *) * ft_2darraylen(env));
	if(!new_env)
		return( ft_printf("Error\n"), NULL);
	printf("after alloc\n");
	category_len = ft_strlen(category);
	ft_printf("Printing ENV\n");
/* 	while(env[i])
	{
		printf("%s\n", env[i]);
		i++;
	} */
	while(env[i])
	{
		if((ft_strncmp(env[i], category, category_len) == 0) && env[i][category_len] == '=')
		{
			ft_printf("detected\n");
			i++;
		}
		new_env[j] = ft_strdup(env[i]);
		j++;
		i++;
	}
	new_env[j] = NULL;
	ft_free2d(env);
	return(new_env);
}

void ft_cd(t_exec *exec, char **env)
{
	char	*path;
	char	*temp;
	int		i;


	i = 0;
	temp = getcwd(NULL, 1024);
	if(category_is_in_env("OLDPWD=", env))
		env = replace_in_env("OLDPWD=", temp, env);
	else
		env = add_to_env(ft_strjoin("OLDPWD=", temp), env);
	free(temp);
	path = exec->args[1]; 
	if (chdir(path) == -1)
		return ;
	temp = getcwd(NULL, 1024);
	if(category_is_in_env("PWD=", env))
		env = replace_in_env("PWD=", temp, env);
	else
		env = add_to_env(ft_strjoin("PWD=", temp), env);
	free(temp);
}

char	**unset(char **args, char **env)
{
	if(category_is_in_env(args[1], env))
	{
		env = remove_from_env(args[1], env);
		ft_printf("in HERE\n");
	}
	return(env);
}

int	built_in(t_exec *exec, char **env, t_data *data)
{
	// if (ft_strncmp(exec->command, "echo", 5) == 0)
	// 	echo(exec->args);
	if (ft_strncmp(exec->command, "cd", 3) == 0)
		ft_cd(exec, env);
	if (ft_strncmp(exec->command, "pwd", 4) == 0)
	{
	 	ft_pwd();
		return(exit(EXIT_SUCCESS), 0);
	}
	// else if (ft_strncmp(exec->command, "export", 7) == 0)
	// 	export(exec->args);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
	 	data->env = unset(exec->args, env);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
	{
		ft_env(env);
		return(exit(EXIT_SUCCESS), 0);
	}
	// else if (ft_strncmp(exec->command, "exit", 5) == 0)
	// 	ftexit(exec->args);
	return (0);
}
