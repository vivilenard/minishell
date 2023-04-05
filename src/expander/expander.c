#include "../../include/minishell.h"

char	*ft_replace_var(char **env, char *dollar)
{
	char	**behind_dollar;
	char	*value;

	value = NULL;
	if (!dollar)
		return (value);
	if (keep_dollar(dollar) == 1)
		return (dollar - 1);
	behind_dollar = if_split_contains_sentence(dollar);
	if (ft_strncmp(behind_dollar[0], "?", 1) == 0)
	{
		value = ft_itoa(g_errno);
		if (ft_strlen(behind_dollar[0]) > 1)
			value = ft_strjoin_free_opt(value, behind_dollar[0] + 1, 1, 0);
	}
	else
		value = search_var_in_env(behind_dollar[0], env);
	value = ft_strjoin_free_opt(value, behind_dollar[1], 1, 0);
	ft_free2d(behind_dollar);
	free(dollar - 1);
	return (value);
}

char	*replace_string(char *s, char **env)
{
	char	*finalstring;
	char	*substr;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (s[i] && s[i] != '$')
		i++;
	finalstring = ft_substr(s, 0, i);
	while (s[i])
	{
		if (s[i] == '$')
		{
			substr = ft_substr(s, i, ft_length_dollar(s + i, '$'));
			look_for_singlequote(finalstring, &flag);
			if (flag == 0)
				substr = ft_replace_var(env, substr + 1);
			finalstring = ft_strjoin_free_opt(finalstring, substr, 1, 1);
		}
		i++;
	}
	if (!is_inquotes(finalstring))
		finalstring = minimize_whitespace(finalstring);
	return (finalstring);
}

char	*look_for_dollar(char *str, char **env)
{
	int		i;
	char	*replaced_str;

	i = 0;
	if (!str || !str[0])
		return (str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			replaced_str = replace_string(str, env);
			if (!replaced_str)
				replaced_str = ft_strdup("");
			return (free(str), replaced_str);
		}
		i++;
	}
	return (str);
}

t_exec	*expand(t_exec *exec, char **env)
{
	char	**tmp_2d;
	char	**args;

	if (var_in_str(exec->command) && ft_strncmp(exec->command, "echo", 5) != 0)
	{
		exec->command = look_for_dollar(exec->command, env);
		tmp_2d = mini_lexer(exec->command);
		args = dupclicate_2d(exec->args);
		ft_free2d(exec->args);
		exec->args = replace_args(tmp_2d, args);
		free(exec->command);
		exec->command = ft_strdup(exec->args[0]);
		ft_free2d(tmp_2d);
		ft_free2d(args);
	}
	return (exec);
}

t_exec	**expander(t_exec **exec, char **env)
{
	int	i;

	i = 0;
	while (exec[i])
	{
		if (exec[i]->command && ft_strncmp(exec[i]->command, "echo", 5) != 0
			&& ft_strncmp(exec[i]->command, "/bin/echo", 10) != 0)
		{
			if (!go_through_exec(exec[i], env))
				return (NULL);
		}
		i++;
	}
	return (exec);
}
