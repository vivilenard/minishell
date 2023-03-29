#include "../../../include/minishell.h"

int count_rm_quotes(char *str)
{
	int		i;
	int		count;
	int		in_quote;
	char	current_quote;

	i = 0;
	count = 0;
	in_quote = 0;
	current_quote = '\0';
	if(!str)
		return(0);
	while(str[i])
	{
		if((str[i] == '\"' || str[i] == '\'') && !in_quote)
		{
			in_quote = 1;
			current_quote = str[i];
			count++;
		}
		else if(str[i] == current_quote && in_quote)
		{
			in_quote = 0;
			current_quote = '\0';
			count ++;
		}
		i++;
	}
	return (count);
}

char *quote_cutter(char *str)
{
	char	*out;
	int		i;
	int		j;
	int		in_quote;
	char	current_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	current_quote = '\0';
	out = (char *)malloc((ft_strlen(str) - count_rm_quotes(str) + 1) * sizeof(char));
	if (!out)
		return(NULL);
	while(str[i])
	{
		if((str[i] == '\"' || str[i] == '\'') && !in_quote)
		{
			in_quote = 1;
			current_quote = str[i];
		}
		else if(str[i] == current_quote && in_quote)
		{
			in_quote = 0;
			current_quote = '\0';
		}
		else
			out[j++] = str[i];
		i++;
	}
	out[j] = '\0';
	return(free(str), out);
}

int is_nnn(char *arg)
{
	size_t	i;

	i = 0;
	if(arg[i] == '-')
		i++;
	else
		return(0);
	if(arg[i] && arg[i] == 'n')
	{
		while(arg[i] && arg[i] == 'n')
			i++;
	}
	else
		return (0);
	if(arg[i])
		return (0);
	return (1);
}

int option_detect(char **args)
{
	int	i;

	i = 1;
	while(args[i])
	{
		if(ft_strncmp(args[i], "-n", 3) != 0 || !is_nnn(args[i]))
			return(i);
		i++;
	}
	return(i);
}

int	ft_echo(t_exec *exec, t_data *data)
{
	char	*out;
	int		end;

	end = 0;
	while (exec->args[end])
		end++;
	if(exec->args[1])
	{
		if (ft_strncmp(exec->args[1], "-n", 3) == 0)
		{
			if(!exec->args[option_detect(exec->args)])
				return(ft_putstr_fd("", 1), EXIT_SUCCESS);
			out = ft_strjoin_s_e(exec->args, option_detect(exec->args), end - 1, " ");
			out = look_for_dollar(out, data->env);
			out = quote_cutter(out);
			ft_putstr_fd(out, 1);
			return(EXIT_SUCCESS);
		}
		else
		{
			if(!exec->args[1])
				return(ft_putendl_fd("", 1), EXIT_SUCCESS);
			out = ft_strjoin_s_e(exec->args, 1, end - 1, " ");
			out = look_for_dollar(out, data->env);
			out = quote_cutter(out);
			ft_putendl_fd(out, 1);
			return(EXIT_SUCCESS);
		}
		free(out);
	}
	else
		ft_putstr_fd("\n", 1);
	return(EXIT_SUCCESS);
}