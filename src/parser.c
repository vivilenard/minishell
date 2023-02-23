#include "../include/minishell.h"

t_token	*write_redirection(t_token *current, t_data *data, int i)
{
	int	j;

	i = 0;
	if(current->content[0] == '<')
	{
		data->execs[i]->input = (char **) malloc(sizeof(char *) * 2);
		if(!data->execs[i]->input)
			exit(0);
		while(j < 2)
		{
			data->execs[i]->input[j] = (char *) malloc(sizeof(char) * ft_strlen(current->content));
			if(!data->execs[i]->input[j])
				exit(0);
			data->execs[i]->input[j] = current->content;
			current = current->next;
			j++;
		}
	}
	else
	{
		data->execs[i]->output = (char **) malloc(sizeof(char *) * 2);
		if(!data->execs[i]->output)
			exit(0);
		while(j < 2)
		{
			data->execs[i]->output[j] = (char *) malloc(sizeof(char) * ft_strlen(current->content));
			if(!data->execs[i]->output[j])
				exit(0);
			data->execs[i]->output[j] = current->content;
			current = current->next;
			j++;
		}
	}
	return (current);
}

int get_command_length(t_token *current)
{
	int len;

	len = 0;
	while (current || current->type != is_pipe || current->type != redirection)
	{
		current = current->next;
		len++;
	}
	return (len);
}

t_token	*write_command(t_token *current, t_data *data, int i)
{
	int	j;
	int command_len;

	j = 0;
	command_len = get_command_length(current);
	data->execs[i]->command = (char **) malloc(get_command_length(current) * sizeof(char *));
	while(j < command_len)
	{
		data->execs[i]->command[j] = current->content;
		current = current->next;
		j++;
	}
	return (current);
}

void write_pipe(t_token *current, t_data *data, int i)
{
	data->execs[i]->output = (char **) malloc(sizeof(char *));
	if(!data->execs[i]->output)
		exit(0);
	data->execs[i]->output[0] = current->content;
}

int parse_tokens(t_data *data)
{
	t_token	*current;
	int		i;

	i = 0;
	current = *data->tokens;
	data->execs = (t_exec **) malloc(sizeof(t_exec **));
	while(current)
	{
		data->execs[i] = (t_exec *) malloc(sizeof(t_exec));
		if(current->type == redirection && current->content[0] == '<')
			current = write_redirection(current, data, i);
		//save redirection sign and folowing target into "input"
		if(current->type == word)
			current = write_command(current, data, i);
		if(current->type == redirection && current->content[0] == '>')
		{
			current = write_redirection(current, data, i);
			current = current->next;
			i++;
		}
		//save redirection sign and folowing target into "output"
		if(current->type == is_pipe && current)
		{
			write_pipe(current, data, i);
			current = current->next;
			i++;
		}
	}
}
