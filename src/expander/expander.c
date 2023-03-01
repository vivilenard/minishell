#include "../include/minishell.h"

/*need to to:
	works for: only variables, but what if words in between???
*/
int		ft_2darraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
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
			content = ft_substr(declaration + 1, i, len);
			return (content);
		}
		i++;
	}
	return (NULL);
}

char	*search_var_in_env(char *s, char **env)
{
	char	*declaration;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (env[i])
	{
		declaration = ft_haystack((const char *)env[i], (const char *)s);
		if (declaration)
			return(take_content(declaration));
		i++;
	}
	return (NULL);
}

char	*take_var(char *s, char **env)
{
	int		i;
	char	**split;
	char	**declaration;
	char	*endword;

	i = 0;
	endword = NULL;
	split = ft_split(s, '$');
	declaration = malloc(sizeof(char *) * (ft_2darraylen(split) + 1));
	while (split[i])
	{
		declaration[i] = search_var_in_env(split[i], env);
		i++;
	}
	i = 0;
	endword = declaration[0];
	i++;
	while (declaration[i])
	{
		endword = ft_strjoin(endword, declaration[i]);
		i++;
	}
	return (endword);
}

char	*replace_var(char *str, char **env)
{
	int		i;
	char	*varname;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			varname = take_var(str, env);
			//printf("%s\n", varname);
			// if (i > 0)
			// 	varname = ft_strjoin(ft_substr(str, 0, i - 1), varname);
			return (varname);
		}
		i++;
	}
	return (str);
}

void	search_array(char **arr, char **env)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		arr[i] = replace_var(arr[i], env);
		i++;
	}
}

t_exec	**expander(t_exec **exec, char **env)
{
	int	i;

	i = 0;
	while (exec[i])
	{
		if (exec[i]->command != NULL)
			exec[i]->command = replace_var(exec[i]->command, env);
		search_array(exec[i]->args, env);
		//printf ("%s\n", exec[i]->args[0]);
		search_array(exec[i]->input, env);
		search_array(exec[i]->output, env);
		i++;
	}
	return (exec);
}