#include "../../../include/minishell.h"

int	exit_too_many_args(void)
{
	ft_putendl_fd("exit", 2);
	ft_putendl_fd("minishell: exit: too many arguments", 2);
	return (1);
}

void	exit_no_numeric(char *str)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(char **args)
{
	long	exit_num;

	exit_num = 0;
	if (!args[1])
		exit(g_errno);
	if (args[2])
		exit_num = exit_too_many_args();
	if (!is_num(args[1]))
	{
		if (!exit_num)
			exit_no_numeric(args[1]);
		exit_num = 255;
	}
	if (!exit_num)
	{
		exit_num = ft_atoi(args[1]);
		if (exit_num < 0 || exit_num > 255)
			exit_num = exit_num % 256;
	}
	return (exit(exit_num), exit_num);
}
