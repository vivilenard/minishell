#include "../../include/minishell.h"

char	*find_correct_path(char **paths, char *command)
{
	int		i;
	char	*backslash_command;
	char	*path_command;

	i = 0;
	backslash_command = ft_strjoin("/", command);
	while (paths[i])
	{
		path_command = ft_strjoin(paths[i], backslash_command);
		if (access(path_command, X_OK) == 0)
			return (free(backslash_command), path_command);
		free (path_command);
		i++;
	}
	free (backslash_command);
	return (NULL);
}

int	is_built_in(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
	 	return(1);
	else if (ft_strncmp(command, "cd", 3) == 0)
	 	return(1);
	else if (ft_strncmp(command, "pwd", 4) == 0)
	 	return(1);
	else if (ft_strncmp(command, "export", 7) == 0)
	 	return(1);
	else if (ft_strncmp(command, "unset", 6) == 0)
	 	return(1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return(1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return(1);
	return(0);
}

int	is_childless_built_in(char *command)
{
	if (ft_strncmp(command, "pwd", 5) == 0)
	 	return(1);
	else if (ft_strncmp(command, "cd", 3) == 0)
	 	return(1);
	else if (ft_strncmp(command, "export", 7) == 0)
	 	return(1);
	else if (ft_strncmp(command, "unset", 6) == 0)
	 	return(1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return(1);
	return(0);
}

char	*get_path(char *command)
{
	char	*env_paths;
	char	**paths;
	char	*correct_path;

	env_paths = getenv("PATH");
	paths = ft_split(env_paths, ':');
	correct_path = find_correct_path(paths, command);
	if(!correct_path)
		return (ft_free2d(paths), command);
		//system ("leaks shell");
	return (ft_free2d(paths), correct_path);
}

// int main ()
// {
// 	printf("%s\n",	get_path("echo"));
// 	system ("leaks shell");
// 	return (0);
// }