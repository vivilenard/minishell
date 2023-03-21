#include "../../../include/minishell.h"

void	write_unset_err_message(char *str)
{
	char	*err_message;
	char	*tmp;

	tmp = ft_strjoin_free_opt("minishell: unset: `", str, 0, 0);
	err_message = ft_strjoin_free_opt(tmp, "': not a valid identifier\n", 1, 0);
	ft_putstr_fd(err_message, 2);
	free(err_message);
	g_errno = 1;
}

int	check_unset(char *str)
{
	int		i;
	int		error;

	error = 0;
	i = 1;
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
		return(write_unset_err_message(str), 0);
	else
		return(1);
}

int	ft_unset(char **args, char ***env)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	while(args[i])
	{
		if(!check_unset(args[i]))
			error = 1;
		if(category_is_in_env(args[1], *env))
			*env = remove_from_env(args[1], *env);
		i++;
	}
	return(error);
}