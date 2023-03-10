#include "../../include/minishell.h"

int	char_is_in_str(char *str, char c)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return(1);
		i++;
	}
	return(0);
}

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if(char_is_in_str(env[i], '='))
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
	new_env = (char **) malloc(sizeof(char *) * (ft_2darraylen(env) + 2));
	if (!new_env)
		return (ft_printf("Error ALLOC AddToEnv\n"), NULL);
	while(env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if(!new_env[i])
			return(NULL);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	ft_free2d(env);
	free(str);
	return(new_env);
}

char **replace_in_env(char *category, char *new_entry, char **env)
{
	int		i;
	char	*category_and_equal;
	char	*full_entry;

	i = 0;
	category_and_equal = ft_strjoin(category, "=");
	full_entry = ft_strjoin_free_opt(category_and_equal, new_entry, 0, 0);
	if(!env || !*env)
		return(NULL);
	while(env[i])
	{
		if(ft_strncmp(env[i], category_and_equal, ft_strlen(category_and_equal)) == 0)
		{
			free(env[i]);
			env[i] = full_entry;
		}
		i++;
	}
	free(category_and_equal);
	return(env);
}

int category_is_in_env(char *category, char **env)
{
	int	i;
	char	*category_and_equal;

	i = 0;
	category_and_equal = ft_strjoin(category, "=");
	while(env[i])
	{
		if(ft_strncmp(env[i], category_and_equal, ft_strlen(category_and_equal)) == 0)
			return(free(category_and_equal), 1);
		i++;
	}
	free(category_and_equal);
	return(0);
}

char	**remove_from_env(char *category, char **env)
{
	char	**new_env;
	char	*category_and_equal;
	int		i;
	int		j;

	i = 0;
	j = 0;
	category_and_equal = ft_strjoin(category, "=");
	new_env = malloc(sizeof(char *) * (ft_2darraylen(env)) + 1);
	if(!new_env)
		return( ft_printf("Error in rm env\n"), NULL);
	while(env[i])
	{
		if(env[i] && ft_strncmp(env[i], category_and_equal, ft_strlen(category_and_equal)) == 0)
			i++;
		if(env[i])
			new_env[j++] = ft_strdup(env[i++]);
	}
	new_env[j] = NULL;
	free(category_and_equal);
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
	if(category_is_in_env("OLDPWD", env))
		env = replace_in_env("OLDPWD", temp, env);
	else
		env = add_to_env(ft_strjoin("OLDPWD", temp), env);
	free(temp);
	path = exec->args[1]; 
	if (chdir(path) == -1)
		return ;
	temp = getcwd(NULL, 1024);
	if(category_is_in_env("PWD", env))
		env = replace_in_env("PWD", temp, env);
	else
		env = add_to_env(ft_strjoin("PWD", temp), env);
	free(temp);
}

char	**ft_unset(char **args, char **env)
{
	if(category_is_in_env(args[1], env))
		env = remove_from_env(args[1], env);
	return(env);
}

char **ft_export(char **args, char **env)
{
	char	*value;
	char	*category;

	value = string_split(args[1], '=', 1, 0);
	category = string_split(args[1], '=', 1, 1);
	if(category_is_in_env(category, env))
		env = replace_in_env(category, value, env);
	else
		env = add_to_env(ft_strdup(args[1]), env);
	free(value);
	free(category);
	return(env);
}

char	*ft_strjoin_s_e(char **args, int start, int end)
{
	int		i;
	char	*out;
	char	*temp;

	i = start;
	if(!args || !*args)
		return(NULL);
	if(i == end && args[i])
		return(ft_strdup(args[i]));
	out = ft_calloc(sizeof(char), 1);
	while(i <= end && args[i])
	{
		temp = ft_strjoin(out, args[i]);
		if(!temp)
			return(free(out),NULL);
		free(out);
		out = ft_strdup(temp);
		free(temp);
		if(args[i + 1] && i < end)
		{
			temp = ft_strjoin(out, " ");
			if(!temp)
				return(free(out),NULL);
			free(out);
			out = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
	return(out);
}


void	ft_echo(t_exec *exec)
{
	char	*out;
	int		end;

	end = 0;
	while(exec->args[end])
		end++;
	if(ft_strncmp(exec->args[1], "-n", 3) == 0)
	{
		out = ft_strjoin_s_e(exec->args, 2, end - 1);
		ft_putstr_fd(out, 1);
	}
	else
	{
		out = ft_strjoin_s_e(exec->args, 1, end - 1);
		ft_putendl_fd(out, 1);
	}
	free(out);
}

int	built_in(t_exec *exec, char **env, t_data *data)
{
	if (ft_strncmp(exec->command, "echo", 5) == 0)
	 	ft_echo(exec);
	if (ft_strncmp(exec->command, "cd", 3) == 0)
		ft_cd(exec, env);
	else if (ft_strncmp(exec->command, "pwd", 4) == 0)
	{
	 	ft_pwd();
		return(exit(EXIT_SUCCESS), 0);
	}
	else if (ft_strncmp(exec->command, "export", 7) == 0)
		data->env = ft_export(exec->args, data->env);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
	 	data->env = ft_unset(exec->args, env);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
	{
		ft_env(env);
		return(exit(EXIT_SUCCESS), 0);
	}
	// else if (ft_strncmp(exec->command, "exit", 5) == 0)
	// 	ftexit(exec->args);
	return (0);
}
