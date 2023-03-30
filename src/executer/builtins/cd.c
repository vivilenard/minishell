#include "../../../include/minishell.h"

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
	char	*path;
	char	*temp;

	temp = getcwd(NULL, 1024);
	if (category_is_in_env("OLDPWD", *env))
		*env = replace_in_env("OLDPWD", temp, *env);
	else
		*env = add_to_env(ft_strjoin("OLDPWD", temp), *env);
	free(temp);
	if (!exec->args[1])
		path = getenv("HOME");
	else
		path = exec->args[1];
	if (chdir(path) == -1)
		return (create_cd_error(path), 1);
	temp = getcwd(NULL, 1024);
	if (category_is_in_env("PWD", *env))
		*env = replace_in_env("PWD", temp, *env);
	else
		*env = add_to_env(ft_strjoin("PWD", temp), *env);
	free(temp);
	return (0);
}