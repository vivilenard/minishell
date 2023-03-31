#include "../../../include/minishell.h"

int	ft_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	if (!cwd)
		return (EXIT_FAILURE);
	ft_putendl_fd(cwd, 1);
	free(cwd);
	return (EXIT_SUCCESS);
}
