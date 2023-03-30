#include "../../../include/minishell.h"

int	update_env(char *category, char *value, char ***env)
{
	char	*temp;

	if (category_is_in_env(category, *env))
		*env = replace_in_env(category, value, *env);
	else
	{
		temp = ft_strjoin(category, "=");
		*env = add_to_env(ft_strjoin_free_opt(temp, value, 1, 0), *env);
	}
	return (g_errno);
}

int	process_export_args(char **args, int i, char ***env)
{
	char	*value;
	char	*category;
	int		error;

	error = 0;
	if (char_is_in_str(args[i], '='))
	{
		value = string_split(args[i], '=', 1, 0);
		value = quote_cutter(value);
		category = string_split(args[i], '=', 1, 1);
		if (!check_export(category, value))
			error = 1;
		if (!error)
			update_env(category, value, env);
		free(value);
		free(category);
	}
	return (g_errno);
}

int	ft_export(char **args, char ***env)
{
	int		i;

	i = 1;
	g_errno = 0;
	if (!args[i])
		export_dclr_message(*env);
	while (args[i])
	{
		process_export_args(args, i, env);
		i++;
	}
	return (g_errno);
}
