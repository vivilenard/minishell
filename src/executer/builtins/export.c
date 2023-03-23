#include "../../../include/minishell.h"

void	write_export_err_message(char *str, char *value)
{
	char	*err_message;
	char	*tmp;
		
	tmp = ft_strjoin_free_opt(str, "=", 0, 0);
	err_message = ft_strjoin_free_opt(tmp, value, 1, 0);
	tmp = ft_strjoin_free_opt("minishell: export: `", err_message, 0, 1);
	err_message = ft_strjoin_free_opt(tmp, "': not a valid identifier\n", 1, 0);
	ft_putstr_fd(err_message, 2);
	free(err_message);
	g_errno = 1;
}

int	check_export(char *str, char *value)
{
	int		i;
	int		error;

	error = 0;
	i = 0;
	if(!ft_isalpha(str[i]) && str[i] != '_')
		error = 1;
	i++;
	while(str[i])
	{
		if(!ft_isdigit(str[i]) && !ft_isalpha(str[i]) && str[i] != '_')
			error = 1;
		i++;
	}
	if(error)
		return(write_export_err_message(str, value), 0);
	else
		return(1);
}

void	export_dclr_message(char **env)
{
	int		i;
	char	*out;

	i = 0;
	while(env[i])
	{
		out = ft_strjoin_free_opt("declare -x ", env[i], 0, 0);
		ft_putendl_fd(out, 2);
		free(out);
		i++;
	}
}

int	ft_export(char **args, char ***env)
{
	char	*value;
	char	*category;
	//char	*temp;
	int		i;
	int		error;

	i = 1;
	error = 0;
	if(!args[i])
		export_dclr_message(*env);
	while(args[i])
	{
		error = 0;
		if(char_is_in_str(args[i], '='))
		{
			value = string_split(args[i], '=', 1, 0);
			value = quote_cutter(value);
			category = string_split(args[i], '=', 1, 1);
			if(!check_export(category, value))
				error = 1;
			if(!error)
				update_env(env, category, value);
			free(value);
			free(category);
		}
		i++;
	}
	return(error);
}
