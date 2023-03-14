#include "../../../include/minishell.h"

void	ft_pwd()
{
	char *cwd;

	cwd = getcwd(NULL, 1024);
	ft_printf("%s\n", cwd);
	free(cwd);
}

void	create_cd_error(char *path)
{
	char	*out;
	char	*temp;

	out = NULL;
	temp = NULL;
	temp = ft_strjoin_free_opt("minishell: cd: ", path, 0, 0);
	out = ft_strjoin_free_opt(temp, ": No such file or directory", 1, 0);
	ft_putendl_fd(out, 1);
	free(out);
}

void	ft_cd(t_exec *exec, char **env)
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
		return (create_cd_error(path), (void)NULL);
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

int is_outer(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

char *quote_cutter(char *str)
{
	char	**temp;
	char	*out;

	temp = NULL;
	if(is_outer(str, '\"') || is_outer(str, '\''))
	{
		ft_printf("IN CONDITION\n");
		if(is_outer(str, '\"'))
			temp = ft_split(str, '\"');
		else if(is_outer(str, '\''))
			temp = ft_split(str, '\'');
		out = NULL;
		out = ft_strjoin_s_e(temp, 0, ft_2darraylen(temp), "");
		free(temp);
		free(str);
		return (out);
	}
	return (str);
}

char	**ft_export(char **args, char **env)
{
	char	*value;
	char	*category;
	char	*temp;

	value = string_split(args[1], '=', 1, 0);
	value = quote_cutter(value);
	category = string_split(args[1], '=', 1, 1);
	if(category_is_in_env(category, env))
		env = replace_in_env(category, value, env);
	else
	{
		temp = ft_strjoin(category, "=");
		env = add_to_env(ft_strjoin_free_opt(temp, value, 1, 0), env);
	}
	free(value);
	free(category);
	return(env);
}

char	*ft_strjoin_s_e(char **args, int start, int end, char *c)
{
	int		i;
	char	*out;
	char	*temp;

	i = start;
	if (!args || !*args)
		return (NULL);
	if (i == end && args[i])
		return (ft_strdup(args[i]));
	out = ft_calloc(sizeof(char), 1);
	while (i <= end && args[i])
	{
		temp = ft_strjoin(out, args[i]);
		if (!temp)
			return (free(out),NULL);
		free(out);
		out = ft_strdup(temp);
		free(temp);
		if (args[i + 1] && i < end)
		{
			temp = ft_strjoin(out, c);
			if (!temp)
				return (free(out),NULL);
			free(out);
			out = ft_strdup(temp);
			free(temp);
		}
		i++;
	}
	return (out);
}

int	built_in(t_exec *exec, char **env, t_data *data)
{
	if (ft_strncmp(exec->command, "echo", 5) == 0)
	 	ft_echo(exec);
	if (ft_strncmp(exec->command, "cd", 3) == 0)
		ft_cd(exec, env);
	else if (ft_strncmp(exec->command, "pwd", 4) == 0)
		return(ft_pwd(), exit(EXIT_SUCCESS), 0);
	else if (ft_strncmp(exec->command, "export", 7) == 0)
		data->env = ft_export(exec->args, data->env);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
	 	data->env = ft_unset(exec->args, env);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
		return(ft_env(env), exit(EXIT_SUCCESS), 0);
	// else if (ft_strncmp(exec->command, "exit", 5) == 0)
	// 	ftexit(exec->args);
	return (0);
}
