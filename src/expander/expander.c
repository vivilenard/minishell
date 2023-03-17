#include "../../include/minishell.h"

char	*ft_replace_var(char **env, char *dollar)
{
	char	**behind_dollar;
	char	*value;

	behind_dollar = if_split_contains_sentence(dollar);
	if (ft_strncmp(behind_dollar[0], "?", 1) == 0)
	{
		value = ft_itoa(g_errno);
		if (ft_strlen(behind_dollar[0]) > 1)
			value = ft_strjoin_free_opt(value, behind_dollar[0] + 1, 1, 0);
	}
	else
	{
		value = search_var_in_env(behind_dollar[0], env);
	}
		value = ft_strjoin_free_opt(value, behind_dollar[1], 1, 0);
	ft_free2d(behind_dollar);
	return (value);
}

char	*replace_string(char *s, char **env)
{
	int		i;
	char	**split_dollar;
	char	*value;
	char	*finalword;

	finalword = NULL;
	split_dollar = ft_split(s, '$');
	i = 0;
	if (s[0] != '$')
	{
		finalword = ft_strdup(split_dollar[0]);
		i++;
	}
	while (split_dollar[i])
	{
		value = ft_replace_var(env, split_dollar[i]);
		finalword = ft_strjoin_free_opt(finalword, value, 1, 0);
		if (value)
			free(value);
		i++;
	}
	ft_free2d(split_dollar);
	return (minimize_whitespace(finalword));
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
			if (!replaced_str)
				replaced_str = ft_strdup(" ");
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
		if (ft_strncmp(exec[i]->command, "echo", 4) != 0)
			expand(exec[i], env);
		i++;
	}
	return (exec);
}

t_exec	*expand(t_exec *exec, char **env)
{
	if (exec->command != NULL)
		exec->command = look_for_dollar(exec->command, env);
	search_array(exec->args, env);
	search_array(exec->input, env);
	search_array(exec->output, env);
	return (exec);
}
