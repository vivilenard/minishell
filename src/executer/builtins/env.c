#include "../../../include/minishell.h"

int update_env(char ***env, char *var, char *value)
{
	size_t	i;
	size_t	len;
	char	**ev;

	i = 0;
	ev = *env;
	len = ft_strlen(var);
	while (ev && ev[i] && ((ev[i][len] != 0 || ev[i][len] != '=')
			&& ft_strncmp(var, ev[i], len)))
		i++;
	if (ev[i] != NULL && ft_strchr(var, '='))
	{
		free(ev[i]);
		if (value == NULL)
			ev[i] = ft_strdup(var);
		else
			ev[i] = ft_strjoin(var, value);
	}
	else if (ev[i] == NULL)
		*env = add_to_env(*env, var, value);
	return (EXIT_SUCCESS);
}

char **add_to_env(char **env, char *var, char *value)
{
	size_t	i;
	char	**new_env;

	i = 0;
	if(!env || !*env)
		return(NULL);
	new_env = (char **) malloc(sizeof(char *) * (ft_2darraylen(env) + 2));
	if (!new_env)
		return (ft_printf("Error ALLOC AddToEnv\n"), NULL);
	while(env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	if(value)
		new_env[i] = ft_strjoin(var, value);
	else
		new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free(env);
	return(new_env);
}

/*char **replace_in_env(char *category, char *new_entry, char **env)
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
			break;
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
} */

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

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if(!env || !*env)
		return(EXIT_FAILURE);
	while (env[i])
	{
		if(char_is_in_str(env[i], '='))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return(EXIT_SUCCESS);
}