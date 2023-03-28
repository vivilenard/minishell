#include "../../include/minishell.h"


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

int	ft_length_dollar(char *s, char c)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	keep_dollar(char *str)
{
	int	n;

	n = 0;
	while (str[n] == '\"' || str[n] == '$' || ft_iswhitespace(str[n]))
		n++;
	if (!str[n])
		return (1);
	return (0);
}

char	*ft_replace_var(char **env, char *dollar)
{
	char	**behind_dollar;
	char	*value;

	value = NULL;
	if (!dollar)
		return (value);
	if (keep_dollar(dollar) == 1)
		return (ft_strdup(dollar - 1));
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

char *replace_string(char *s, char **env)
{
	char	*finalstring;
	char	*substr;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	finalstring = NULL;
	(void)env;
	while(s[i] && s[i] != '$')
		i++;
	finalstring = ft_substr(s, 0, i);
	//look_for_singlequote(finalstring, &flag);
	while (s[i])
	{
		if (s[i] == '$')
		{
				substr = ft_substr(s, i, ft_length_dollar(s + i, '$'));
				look_for_singlequote(finalstring, &flag);
				printf("substr %s\n", substr);
				//printf("flag %d\n", flag);
				if (flag == 0)
					substr = ft_replace_var(env, substr + 1);
				printf("substr %s\n", substr);
				finalstring = ft_strjoin_free_opt(finalstring, substr, 1, 1);
				//printf("substr %s\n", substr);
		}
		i++;
	}
	//printf("finalstr %s\n", finalstring);
	return (minimize_whitespace(finalstring));
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
			//printf("rep %s\n", replaced_str);
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
		if (ft_strncmp(exec[i]->command, "echo", 5) != 0
			&& ft_strncmp(exec[i]->command, "/bin/echo", 10) != 0)
			expand(exec[i], env);
		i++;
	}
	return (exec);
}

t_exec	*expand(t_exec *exec, char **env)
{
	//printf("EXPANDER\n");
	if (exec->command != NULL)
	{
		exec->command = cut_outer_quotes(exec->command);
		exec->command = look_for_dollar(exec->command, env);
		exec->command = get_path(exec->command);
	}
	search_array(exec->args, env);
	search_array(exec->input, env);
	search_array(exec->output, env);
	return (exec);
}


	// if (s[i] == '$' && s[i + 1] == '$')
	// {
	// 	while (s[i] == '$' && s[i + 1] == '$')
	// 		i++;
	// 	finalword = ft_substr(s, 0, i + 1);
	// }
	// printf("string %s\n", s);
	// printf("finalword %s\n", finalword);
	// printf("split %s, %d\n", split_dollar[0], flag);




// char	*replace_string(char *s, char **env)
// {
// 	int		i;
// 	char	**split_dollar;
// 	char	*value;
// 	char	*finalword;
// 	int		flag;

// 	finalword = NULL;
// 	flag = 0;
// 	split_dollar = ft_split(s, '$');
// 	if (!split_dollar[0])
// 		return (s);
// 	i = 0;
// 	if (s[i] != '$')
// 	{
// 		finalword = ft_strdup(split_dollar[0]);
// 		i++;
// 	}

// 	while (split_dollar[i])
// 	{
// 		look_for_singlequote(finalword, &flag);
// 		if (flag == 0)
// 			value = ft_replace_var(env, split_dollar[i]);
// 		else if (flag == 1)
// 			value = ft_strjoin_free_opt("$", split_dollar[i], 0, 0);
// 		finalword = ft_strjoin_free_opt(finalword, value, 1, 1);
// 		i++;
// 	}
// 	ft_free2d(split_dollar);
// 	return (minimize_whitespace(finalword));
// 	//return (finalword);
// }