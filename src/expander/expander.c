#include "../../include/minishell.h"

char	*ft_replace_var(char **env, char *dollar)
{
	char	**behind_dollar;
	char	*value;

	value = NULL;
	if (!dollar)
		return (value);
	behind_dollar = if_split_contains_sentence(dollar);
	//ft_printf("bd0 %s, bd1 %s\n", behind_dollar[0], behind_dollar[1]);
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
	//ft_printf("value %s\n", value);
	ft_free2d(behind_dollar);
	return (value);
}

void	look_for_singlequote(char *str, int *flag)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\'')
			ft_switchflag(flag);
		i++;
	}
}

char	*replace_string(char *s, char **env)
{
	int		i;
	char	**split_dollar;
	char	*value;
	char	*finalword;
	int		flag;

	finalword = NULL;
	flag = 0;
	split_dollar = ft_split(s, '$');
	if (!split_dollar[0])
		return (s);
	i = 0;
	if (s[i] != '$')
	{
		finalword = ft_strdup(split_dollar[0]);
		i++;
	}
	// printf("string %s\n", s);
	// printf("finalword %s\n", finalword);
	// printf("split %s, %d\n", split_dollar[0], flag);
	while (split_dollar[i])
	{
		look_for_singlequote(finalword, &flag);
		if (flag == 0)
			value = ft_replace_var(env, split_dollar[i]);
		else if (flag == 1)
			value = ft_strjoin_free_opt("$", split_dollar[i], 0, 0);
		finalword = ft_strjoin_free_opt(finalword, value, 1, 1);
		i++;
	}
	ft_free2d(split_dollar);
	return (minimize_whitespace(finalword));
	//return (finalword);
}

char	*look_for_dollar(char *str, char **env)
{
	int		i;
	char	*replaced_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && ft_strlen(str) > 1)
		{	
			replaced_str = replace_string(str, env);
			//printf("hi\n");
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
	//printf("EXPANDER\n");
	if (exec->command != NULL)
		exec->command = look_for_dollar(exec->command, env);
	search_array(exec->args, env);
	search_array(exec->input, env);
	search_array(exec->output, env);
	return (exec);
}
