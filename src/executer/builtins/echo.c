#include "../../../include/minishell.h"

int is_outer(char *str, char c)
{
	if (str[0] == c && str[ft_strlen(str)] == c)
		return (1);
	return (0);
}


char *quote_cutter(char *str)
{
	char	**temp;
	char	*out;

	temp = NULL;
	if(is_outer(str, '\"') || is_outer(str, '\''))
	{
		ft_printf("IN CONDITION\n");
		if(is_outer(str, '\"'))
			temp = ft_split(str, '\"');
		else if(is_outer(str, '\''))
			temp = ft_split(str, '\'');
		out = NULL;
		out = ft_strjoin_s_e(temp, 0, ft_2darraylen(temp));
		return (out);
	}
	return (str);
}

void	ft_echo(t_exec *exec)
{
	char	*out;
	int		end;

	end = 0;
	while (exec->args[end])
		end++;
	if (ft_strncmp(exec->args[1], "-n", 3) == 0)
	{
		out = ft_strjoin_s_e(exec->args, 2, end - 1);
		ft_printf("%s\n", out);
		out = quote_cutter(out);
		ft_putstr_fd(out, 1);
	}
	else
	{
		out = ft_strjoin_s_e(exec->args, 1, end - 1);
		ft_printf("%s\n", out);
		out = quote_cutter(out);
		ft_putendl_fd(out, 1);
	}
	free(out);
}