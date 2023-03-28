#include "../../../include/minishell.h"

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
	new_env = malloc(sizeof(char *) * (ft_2darraylen(env) + 2));
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
		ft_putendl_fd(env[i], 1);
		i++;
	}
	return(EXIT_SUCCESS);
}