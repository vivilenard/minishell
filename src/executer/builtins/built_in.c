#include "../../../include/minishell.h"

int	ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 1024);
	if(!cwd)
		return (EXIT_FAILURE);
	ft_printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}

void	create_cd_error(char *path)
{
	char	*out;
	char	*temp;

	out = NULL;
	temp = NULL;
	temp = ft_strjoin_free_opt("minishell: cd: ", path, 0, 0);
	out = ft_strjoin_free_opt(temp, ": No such file or directory", 1, 0);
	ft_putendl_fd(out, 2);
	free(out);
}

int	ft_cd(t_exec *exec, char ***env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 1);
	if(!exec->args[1] || ft_strlen(exec->args[1]) == 0)
	{
		new_pwd = getenv("HOME");
		if(chdir(new_pwd) != 0)
			return(free(old_pwd), EXIT_FAILURE);
		update_env(env, "OLDPWD", old_pwd);
		update_env(env, "PWD", new_pwd);
		return(free(old_pwd), EXIT_SUCCESS);
	}
	else if (chdir(exec->args[1]) != 0)
	{
		ft_putstr_fd(exec->args[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (free(old_pwd), EXIT_FAILURE);
	}
	new_pwd = getcwd(NULL, 1);
	update_env(env, "OLDPWD=", old_pwd);
	update_env(env, "PWD=", new_pwd);
	return (free(old_pwd), free(new_pwd), EXIT_SUCCESS);
}

int is_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return(0);
		i++;
	}
	return(1);
}

int ft_exit(char **args)
{
	long	exit_num;
	
	if(!args[1])
		exit(g_errno);
	if(args[2])
	{
		ft_putendl_fd("exit", 2);
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (exit(g_errno), g_errno);
	}
	if(!is_num(args[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (exit(255), 255);;
	}
	exit_num = ft_atoi(args[1]);
	if(exit_num < 0 || exit_num > 255)
		exit_num = exit_num % 256;
	return(exit(exit_num), exit_num);
}

int	built_in(t_exec *exec, char ***env, t_data *data)
{
	if (ft_strncmp(exec->command, "echo", 5) == 0 || ft_strncmp(exec->command, "/bin/echo", 10) == 0)
	 	return (g_errno = ft_echo(exec, data), 1);
	else if (ft_strncmp(exec->command, "cd", 3) == 0)
		return(g_errno = ft_cd(exec, env), 1);
	else if (ft_strncmp(exec->command, "pwd", 4) == 0)
		return(g_errno = ft_pwd(), 1);
	else if (ft_strncmp(exec->command, "export", 7) == 0)
		return (g_errno = ft_export(exec->args, &data->env), 1);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
		return (g_errno = ft_unset(exec->args, &data->env), 1);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
		return(g_errno = ft_env(data->env), 1);
	else if (ft_strncmp(exec->command, "exit", 5) == 0)
	 	return(g_errno = ft_exit(exec->args), 1);
	return (0);
}

int	built_in_child(t_exec *exec, char ***env, t_data *data)
{
	if (ft_strncmp(exec->command, "echo", 5) == 0 || ft_strncmp(exec->command, "/bin/echo", 10) == 0)
	 	return (g_errno = ft_echo(exec, data), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "cd", 3) == 0)
		return(g_errno = ft_cd(exec, env), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "pwd", 4) == 0)
		return(g_errno = ft_pwd(), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "export", 7) == 0)
		return (g_errno = ft_export(exec->args, &data->env), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "unset", 6) == 0)
		return (g_errno = ft_unset(exec->args, &data->env), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "env", 4) == 0)
		return(g_errno = ft_env(data->env), exit(g_errno), 1);
	else if (ft_strncmp(exec->command, "exit", 5) == 0)
	 	return(g_errno = ft_exit(exec->args), exit(g_errno), 1);
	return (0);
}
 