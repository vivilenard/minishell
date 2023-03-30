#include "../../include/minishell.h"

int	look_for_singlequote(char *str, int *flag)
{
	int	i;
	int	doubleflag;

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

t_exec	*go_through_exec(t_exec *exec, char **env)
{
	char	*tmp;

	tmp = NULL;
	exec = expand(exec, env);
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
