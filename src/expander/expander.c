#include "../../include/minishell.h"

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
			return(free(tmp), take_content(env[i]));
		i++;
	}
	return (free(tmp), NULL);
}

char	**if_split_contains_sentence(const char *dollar)
{
	char	**behind_dollar;
	int		i;
	int		n;

	i = 0;
	n = 0;
	behind_dollar = malloc(sizeof(char *) * 3);
	while (dollar[i])
	{
		if (ft_iswhitespace(dollar[i]))
		{
			behind_dollar[n] = ft_substr(dollar, 0, i);
			n++;
			behind_dollar[n] = ft_strdup(dollar + i);
			behind_dollar[n + 1] = NULL;
			return (behind_dollar);
		}
		i++;
	}
	behind_dollar[n] = ft_strdup(dollar);
	behind_dollar[n + 1] = NULL;
	return (behind_dollar);
}

char	*replace_var(char *s, char **env)
{
	int		i;
	char	**dollar;
	char	**replacement;
	char	*finalword = NULL;
	char	**behind_dollar;
	char	flag;

	flag = 0;
	if (s[0] != '$')
		flag = 1;
	dollar = ft_split(s, '$');
	replacement = malloc(sizeof(char *) * (ft_2darraylen(dollar) + 1));
	if (flag == 1)
	 	finalword = dollar[0];
	i = flag;
	while (dollar[i])
	{
		behind_dollar = if_split_contains_sentence(dollar[i]);
		replacement[i] = search_var_in_env(behind_dollar[0], env);
		replacement[i] = ft_strjoinandfree(replacement[i], behind_dollar[1]);
		if (replacement[i])
			finalword = ft_strjoinandfree(finalword, replacement[i]);
		ft_free2d(behind_dollar);
		i++;
	}
	replacement[i] = NULL;
	ft_free2d(dollar);
	ft_free2d(replacement);
	return (finalword);
}

char	*look_for_dollar(char *str, char **env)
{
	int		i;
	char	*replaced_str;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{	
			replaced_str = replace_var(str, env);
			return (free(str), replaced_str);
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
		arr[i] = look_for_dollar(arr[i], env);
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
		{
			exec[i]->command = look_for_dollar(exec[i]->command, env);
		}
		search_array(exec[i]->args, env);
		search_array(exec[i]->input, env);
		search_array(exec[i]->output, env);
		i++;
	}
	system ("leaks shell");
	return (exec);
}