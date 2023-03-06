#include "../include/minishell.h"

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
	return (NULL);
}

char	*get_path(char *command)
{
	char	*env_paths;
	char	**paths;
	char	*correct_path;

	env_paths = getenv("PATH");
	paths = ft_split(env_paths, ':');
	correct_path = find_correct_path(paths, command);
	ft_free2d(paths);
	return (correct_path);
}

// int main ()
// {
// 	printf("%s\n",	get_path("echo"));
// 	system ("leaks shell");
// 	return (0);
// }