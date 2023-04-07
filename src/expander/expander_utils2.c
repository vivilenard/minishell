#include "../../include/minishell.h"

int	look_for_singlequote(char *str, int *flag)
{
	int	i;
	int	doubleflag;

	i = 0;
	doubleflag = 0;
	*flag = 0;
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

void	command_not_found(char *s, t_data *data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(s, 2);
	if (ft_strlen(s) > 1 && s[ft_strlen(s) - 1] == '/')
	{
		ft_putstr_fd(": is a directory\n", 2);
		if (ft_strncmp(s, "/bin/", 6) == 0)
			ft_exit_free(data, 126);
		ft_exit_free(data, 127);
	}
	if (s[0] && (ft_strncmp(s, "./", 2) == 0 || ft_strncmp(s, "/", 1) == 0))
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_exit_free(data, 127);
	}
	ft_putstr_fd(": command not found\n", 2);
	ft_exit_free(data, 127);
}

t_exec	*go_through_exec(t_exec *exec, char **env, t_data *data)
{
	char	*tmp;

	tmp = NULL;
	exec = expand(exec, data->env);
	if (exec->command != NULL)
	{
		tmp = ft_strdup(exec->args[0]);
		exec->args[0] = quote_cutter(exec->args[0]);
		if (tmp[0] && (!exec->args[0][0] || only_whitespace(exec->args[0])))
		{
			g_errno = 127;
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(exec->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			return (free(tmp), free_exec(data, *exec->input), NULL);
		}
		free(tmp);
		free(exec->command);
		exec->command = ft_strdup(exec->args[0]);
		exec->command = get_path(exec->command, env);
	}
	search_array(exec->args, env);
	search_array(exec->input, env);
	search_array(exec->output, env);
	return (exec);
}
