#include "../../include/minishell.h"


int	look_for_singlequote(char *str, int *flag)
{
	int	i;
	int doubleflag;

	i = 0;
	doubleflag = 0;
	while (str && str[i])
	{
		if (str[i] == '\"')
			ft_switchflag(&doubleflag);
		if (doubleflag == 0 && str[i] == '\'')
			ft_switchflag(flag);
		i++;
	}
	return (*flag);
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
	while(s[i] && s[i] != '$')
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
	return (minimize_whitespace(finalstring));
}

char	*look_for_dollar(char *str, char **env)
{
	int		i;
	char	*replaced_str;

	i = 0;
	if(!str || !str[0])
		return(str);
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

t_exec	**expander(t_exec **exec, char **env)
{
	int	i;

	i = 0;
	while (exec[i])
	{
		if (exec[i]->command && ft_strncmp(exec[i]->command, "echo", 5) != 0
			&& ft_strncmp(exec[i]->command, "/bin/echo", 10) != 0)
			{
				if(!expand(exec[i], env))
					return (NULL);
			}
		i++;
	}
	return (exec);
}

int var_in_str(char *str)
{
    int i;
    int sq_flag;

    sq_flag = 0;
    i = 0;
    while (str[i])
    {
        if (sq_flag && str[i] =='\'')
            sq_flag = 0;
        else if (!sq_flag && str[i] == '\'')
            sq_flag = 1;
        if (str[i] == '$' && !sq_flag && str[i + 1])
            return(1);
        i++;
    }
    return(0);
}

char **join_2d_array(char **s1, char **s2)
{
    char    **out;
    int     i;
    int     j;

    if(!s1 && !s2)
        return (NULL);
    if(!s1)
        return (s2);
    if(!s2)
        return (s1);
    i = 0;
    j = 0;
    out = (char **) malloc(sizeof(char *) * (ft_2darraylen(s1) + ft_2darraylen(s2) + 1));
    if(!out)
        return(NULL);
    while(s1[j])
        out[i++] = ft_strdup(s1[j++]);
    j = 0;
    while (s2[j])
        out[i++] = ft_strdup(s2[j++]);
    out[i] = NULL;
    return(out);
}

char **mini_lexer(char *str)
{
	char	**split;
	int		strnumber;

	if (quote_is_unbalanced(recognize_quote(str, '\''), recognize_quote(str, '\"')) == -1)
		return (0);
	str = ft_strtrim(str, "\n\t\v\f\r ");
	strnumber = countstrs(str) + 1;
	split = NULL;
	split = allocate(split, strnumber);
	create_strings(split, str);
	split[strnumber] = NULL;
	free(str);
	return(split);
}

char **replace_args(char **c_args, char **args, int exp_cycle)
{
	int		i;
	int		j;
	int		arg_len;
	char	**new_args;

	i = 0;
	j = 0;
	(void)exp_cycle;
	arg_len = ft_2darraylen(c_args) + ft_2darraylen(args);
	new_args = (char **) malloc (sizeof(char *) * (arg_len));
	if (!new_args)
		return (NULL);
	while(c_args && c_args[i])
	{
		new_args[i] = ft_strdup(c_args[j]);
		i++;
		j++;
	}
	j = 1;
	while(args[j])
		new_args[i++] = ft_strdup(args[j++]);
	new_args[i] = NULL;
	return(new_args);
}

t_exec *prep_expand(t_exec *exec, char **env)
{
	char	**args;
	char	**tmp_2d;
	char	*tmp;
	int		exp_cycle;

	tmp = NULL;
	exp_cycle = 0;
	if(var_in_str(exec->command) && ft_strncmp(exec->command, "echo", 5) != 0)
	{
		while(var_in_str(exec->command))
		{
			exec->command = look_for_dollar(exec->command, env);
			exp_cycle++;
		}
		tmp_2d = mini_lexer(exec->command);
		args = dupclicate_2D(exec->args);
		ft_free2d(exec->args);
		exec->args = replace_args(tmp_2d, args, exp_cycle);
		ft_free2d(args);
		ft_free2d(tmp_2d);
		tmp = exec->command;
		exec->command = ft_strdup(exec->args[0]);
		free(tmp);
	}
	return(exec);
}

t_exec	*expand(t_exec *exec, char **env)
{
	char *tmp;

	tmp = NULL;
	exec = prep_expand(exec, env);
	if (exec->command != NULL)
	{
		tmp = exec->args[0];
		exec->args[0] = quote_cutter(exec->command);
		free(tmp);
		exec->command = ft_strdup(exec->args[0]);
		exec->command = get_path(exec->command, env);
	}
	search_array(exec->args, env);
	search_array(exec->input, env);
	search_array(exec->output, env);
	return (exec);
}

		//tmp = ft_substr(str, 0, i);
		//look_for_singlequote(tmp, &quoteflag);
		//free(tmp);

	