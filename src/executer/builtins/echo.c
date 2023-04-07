#include "../../../include/minishell.h"

int	is_nnn(char *arg)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(arg);
	tmp = quote_cutter(tmp);
	if (tmp[i] == '-')
		i++;
	else
		return (free(tmp), 0);
	if (tmp[i] && tmp[i] == 'n')
	{
		while (tmp[i] && tmp[i] == 'n')
			i++;
	}
	else
		return (free(tmp), 0);
	if (tmp[i])
		return (free(tmp), 0);
	return (free(tmp), 1);
}

int	option_detect(char **args)
{
	int		i;

	i = 1;
	while (args[i])
	{
		if (!is_nnn(args[i]))
			return (i);
		i++;
	}
	return (i);
}

void	out_echo_str(char **args, char **env, char *out, int end)
{
	if (is_nnn(args[1]))
	{
		if (!args[option_detect(args)])
			return (ft_putstr_fd("", 1), (void) NULL);
		if (ft_2darraylen(args) > 2)
			out = ft_strjoin_s_e(args, option_detect(args),
					end, " ");
		out = look_for_dollar(out, env);
		out = quote_cutter(out);
		ft_putstr_fd(out, 1);
	}
	else
	{
		if (!args[1])
			return (ft_putendl_fd("", 1), (void) NULL);
		out = ft_strjoin_s_e(args, 1, end, " ");
		out = look_for_dollar(out, env);
		out = quote_cutter(out);
		ft_putendl_fd(out, 1);
	}
	free(out);
}

int	ft_echo(t_exec *exec, t_data *data)
{
	char	*out;
	int		end;

	end = 0;
	out = NULL;
	while (exec->args[end])
		end++;
	if (exec->args[1])
		return (out_echo_str(exec->args, data->env, out, end), EXIT_SUCCESS);
	else
		ft_putendl_fd("", 1);
	return (EXIT_SUCCESS);
}
