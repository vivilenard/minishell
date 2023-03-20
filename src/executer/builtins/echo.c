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

void	ft_echo(t_exec *exec, t_data *data)
{
	char	*out;
	int		end;

	end = 0;
	while (exec->args[end])
		end++;
	if (ft_strncmp(exec->args[1], "-n", 3) == 0)
	{
		out = ft_strjoin_s_e(exec->args, 2, end - 1, " ");
		out = look_for_dollar(out, data->env);
		out = quote_cutter(out);
		ft_putstr_fd(out, 1);
	}
	else
	{
		out = ft_strjoin_s_e(exec->args, 1, end - 1, " ");
		printf("out %s\n", out);
		out = look_for_dollar(out, data->env);
		out = quote_cutter(out);
		ft_putendl_fd(out, 1);
	}
	free(out);
}