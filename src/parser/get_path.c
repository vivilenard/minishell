#include "../../include/minishell.h"

char	*find_correct_path(char **paths, char *command)
{
	int		i;
	char	*backslash_command;
	char	*path_command;

	i = 0;
	if (ft_strncmp(command, "..", 3) == 0)
		return (ft_strdup(command));
	if (ft_strncmp(command, ".", 2) == 0)
		return (ft_strdup(command));
	if (ft_haystack(command, "./") || ft_haystack(command, "/"))
		return (NULL);
	backslash_command = ft_strjoin("/", command);
	while (paths && paths[i])
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
		return (1);
	else if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

char	*ft_searchbinary(char **env, char *s)
{
	int	i;

	i = 0;
	while (env[i] && *env[i])
	{
		if (ft_haystack(env[i], s) != NULL)
			return (env[i]);
		i++;
	}
	return (NULL);
}

char	*get_path(char *command, char **env)
{
	char	*env_paths;
	char	**paths;
	char	*correct_path;

	correct_path = NULL;
	if (is_built_in(command) || !ft_strlen(command))
		return (command);
	env_paths = ft_searchbinary(env, "PATH");
	paths = ft_split(env_paths, ':');
	correct_path = find_correct_path(paths, command);
	if (!correct_path)
		return (ft_free2d(paths), command);
	return (ft_free2d(paths), free (command), correct_path);
}
