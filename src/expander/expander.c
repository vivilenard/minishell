#include "../../include/minishell.h"

char	*replace_string(char *s, char **env)
{
	int		i;
	char	**dollar;
	char	*value;
	char	*finalword;

	finalword = NULL;
	dollar = ft_split(s, '$');
	i = 0;
	if (s[0] != '$')
	{
		finalword = ft_strdup(dollar[0]);
		i++;
	}
	while (dollar[i])
	{
		value = ft_replace_var(env, dollar[i]);
		finalword = ft_strjoinandfree(finalword, value);
		if (value)
			free(value);
		i++;
	}
	ft_free2d(dollar);
	return (finalword);
}

char	*look_for_dollar(char *str, char **env)
{
	int		i;
	char	*replaced_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{	
			replaced_str = replace_string(str, env);
			return (free(str), replaced_str);
		}
		i++;
	}
	return (str);
}

t_exec	**expander(t_exec **exec, char **env)
{
	int	i;

	i = 0;
	while (exec[i])
	{
		if (exec[i]->command != NULL)
			exec[i]->command = look_for_dollar(exec[i]->command, env);
		search_array(exec[i]->args, env);
		search_array(exec[i]->input, env);
		search_array(exec[i]->output, env);
		i++;
	}
	return (exec);
}
