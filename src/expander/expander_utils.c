#include "../../include/minishell.h"

void	search_array(char **arr, char **env)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		arr[i] = look_for_dollar(arr[i], env);
		i++;
	}
}

char	*take_content(char *declaration)
{
	int		i;
	int		len;
	char	*content;

	content = NULL;
	len = 0;
	i = 0;
	while (declaration[i])
	{
		if (declaration[i] == '=')
		{
			len = ft_strlen(declaration + i + 1);
			content = ft_substr(declaration, i + 1, len);
			return (content);
		}
		i++;
	}
	return (NULL);
}

char	*search_var_in_env(char *var, char **env)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	n = 0;
	tmp = ft_strjoin(var, "=");
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
			return (free(tmp), take_content(env[i]));
		i++;
	}
	return (free(tmp), NULL);
}
