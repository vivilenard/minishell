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
	g_errno = 2;
}

void	ft_cd(t_exec *exec, char **env)
{
	char	*path;
	char	*temp;

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

int	built_in(t_exec *exec, char **env, t_data *data)
{
	if (ft_strncmp(exec->command, "echo", 5) == 0 || ft_strncmp(exec->command, "/bin/echo", 10) == 0)
	 	return (ft_echo(exec, data), 1);
	else if (ft_strncmp(exec->command, "cd", 3) == 0)
		return(ft_cd(exec, env), 1);
	else if (ft_strncmp(exec->command, "pwd", 4) == 0)
		return(ft_pwd(), exit(EXIT_SUCCESS), 1);
	else if (ft_strncmp(exec->command, "export", 7) == 0)
		return (g_errno = ft_export(exec->args, &data->env), 1);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
		return (g_errno = ft_unset(exec->args, &data->env), 1);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
		return(ft_env(data->env), exit(EXIT_SUCCESS), 1);
	// else if (ft_strncmp(exec->command, "exit", 5) == 0)
	// 	ftexit(exec->args);
	return (0);
}
