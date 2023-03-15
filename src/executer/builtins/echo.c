#include "../../../include/minishell.h"

void	ft_echo(t_exec *exec)
{
	char	*out;
	int		end;
	//char	*temp;

	end = 0;
	while (exec->args[end])
		end++;
	if (ft_strncmp(exec->args[1], "-n", 3) == 0)
	{
		out = ft_strjoin_s_e(exec->args, 2, end - 1, " ");
		out = quote_cutter(out);
		ft_putstr_fd(out, 1);
	}
	else
	{
		out = ft_strjoin_s_e(exec->args, 1, end - 1, " ");
		out = quote_cutter(out);
		ft_putendl_fd(out, 1);
	}
	free(out);
}