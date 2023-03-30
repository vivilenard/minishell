#include "../include/minishell.h"

int	is_char(char place, char c)
{
	if (place == c)
		return (1);
	return (0);
}

void	free_tokens(t_data *data)
{
	t_token	*current;
	t_token	*tmp;

	if (data->tokens)
	{
		current = data->tokens;
		while (current)
		{
			tmp = current->next;
			free(current->content);
			current->content = NULL;
			free(current);
			current = tmp;
		}
		current = NULL;
	}
}

void free_exec(t_data *data, char *input)
{
	int i;

	i = 0;
	while (data->execs[i])
	{
		if (data->execs[i]->command)
			free(data->execs[i]->command);
		if (data->execs[i]->args)
			ft_free2d(data->execs[i]->args);
		if (data->execs[i]->input)
			ft_free2d(data->execs[i]->input);
		if (data->execs[i]->output)
			ft_free2d(data->execs[i]->output);
		free(data->execs[i]);
		data->execs[i] = NULL;
		i++;
	}
	free(data->execs);
	data->execs = NULL;
	if (input)
		free(input);
}

void	free_data(t_data *data)
{
	if (data->execs)
		free_exec(data, NULL);
	if (data->env)
		ft_free2d(data->env);
	free(data->promptline);
	if (data)
		free(data);
}

char	**dupclicate_2d(char **str)
{
	int		i;
	int		size;
	char	**copy;

	size = 0;
	i = 0;
	if (!str || !*str)
		return (NULL);
	while (str[size])
		size++;
	copy = (char **) malloc(sizeof(char *) * (size + 1));
	if (!copy)
		return (NULL);
	while (str[i])
	{
		copy[i] = ft_strdup(str[i]);
		if (!copy[i])
			return (NULL);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

t_data	*init_data(char **env, int args, char **argv)
{
	t_data	*data;

	(void)args;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		return (free(data->promptline), exit(EXIT_FAILURE), NULL);
	data->execs = NULL;
	data->tokens = NULL;
	data->promptline = prompt(data);
	data->env = dupclicate_2D(env);
	return (data);
}

void	reset_data(t_data *data)
{
	free(data->promptline);
	data->promptline = prompt(data);
	data->tokens = NULL;
	data->execs = NULL;
	data->pipeflag = 0;
	data->arg_count = 0;
	data->exec_count = 0;
}
