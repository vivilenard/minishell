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

char	**if_split_contains_sentence(char *dollar)
{
	char	**behind_dollar;
	int		i;
	int		n;
	int		whitespace;

	i = 0;
	n = 0;
	whitespace = 0;
	behind_dollar = malloc(sizeof(char *) * 3);
	while (dollar[i])
	{
		if (ft_iswhitespace(dollar[i]))
		{
			behind_dollar[n] = ft_substr(dollar, 0, i);
			//printf("BD %s\n", behind_dollar[n]);
			n++;
			behind_dollar[n] = ft_strdup(dollar + i);
			//printf("BD %s\n", behind_dollar[n]);
			return (free (dollar), behind_dollar);
		}
		i++;
	}
	behind_dollar[n] = dollar;
	behind_dollar[n + 1] = NULL;
	return (free (dollar), behind_dollar);
}

char	*take_var(char *s, char **env)
{
	int		i;
	char	**dollar;
	char	**replacement;
	char	*finalword = "";
	char	**behind_dollar;
	char	flag;

	//finalword = NULL;
	flag = 0;
	if (s[0] != '$')
		flag = 1;
	dollar = ft_split(s, '$');
	ft_put2dstr_fd(dollar, 2);
	replacement = malloc(sizeof(char *) * (ft_2darraylen(dollar) + 1));
	if (flag == 1)
	 	finalword = dollar[0];
	i = flag;
	while (dollar[i])
	{
		behind_dollar = if_split_contains_sentence(dollar[i]);
		replacement[i] = search_var_in_env(behind_dollar[0], env);
		printf("BD: %s, REP: replacement: %s\n", behind_dollar[i], replacement[i]);
		if (behind_dollar[1])
			replacement[i] = ft_strjoin(replacement[i], behind_dollar[1]);
		printf("REP %s\n", replacement[i]);
		finalword = ft_strjoin(finalword, replacement[i]);
		printf("fw: %s\n", finalword);
		ft_free2d(behind_dollar);
		i++;
	}
	replacement[i] = NULL;
	free(dollar);
	return (finalword);
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
		{
			exec[i]->command = replace_var(exec[i]->command, env);
		}
		search_array(exec[i]->args, env);
		//printf ("%s\n", exec[i]->args[0]);
		search_array(exec[i]->input, env);
		search_array(exec[i]->output, env);
		i++;
	}
	return (exec);
}