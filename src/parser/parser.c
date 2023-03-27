#include "../../include/minishell.h"

void init_exec(t_data *data, t_token *current)
{
	data->execs[data->exec_count] = ft_calloc(sizeof(t_exec) + 1, 1);
	data->execs[data->exec_count]->pipe_num = exec_has_pipe(current);
	data->execs[data->exec_count]->input_num = get_input_num(current) * 2 + data->pipeflag;
	data->execs[data->exec_count]->output_num = get_output_num(current) * 2 + data->execs[data->exec_count]->pipe_num;
	data->execs[data->exec_count]->arg_num = get_arg_num(current);
	data->execs[data->exec_count]->input_written = 0;
	data->execs[data->exec_count]->output_written = 0;

/* 	ft_printf("INPUT: %i\n", data->execs[data->exec_count]->input_num);
	ft_printf("OUTPUT: %i\n", data->execs[data->exec_count]->output_num);
	ft_printf("PIPE: %i\n", data->execs[data->exec_count]->pipe_num);
	ft_printf("ARGS: %i\n", data->execs[data->exec_count]->arg_num); */

	data->execs[data->exec_count]->command = NULL;
	data->execs[data->exec_count]->args = (char **) malloc(sizeof(char *) * (data->execs[data->exec_count]->arg_num + 1));
	data->execs[data->exec_count]->args[data->execs[data->exec_count]->arg_num] = NULL;
	data->execs[data->exec_count]->input = (char **) malloc(sizeof(char *) * (data->execs[data->exec_count]->input_num + data->pipeflag + 1));
	data->execs[data->exec_count]->input[data->execs[data->exec_count]->input_num] = NULL;
	data->execs[data->exec_count]->output = (char **) malloc(sizeof(char *) * (data->execs[data->exec_count]->output_num + 1));
	data->execs[data->exec_count]->output[data->execs[data->exec_count]->output_num] = NULL;
}

t_token	*write_redirection(t_data *data, t_token *current)
{
	int	j;

	if(current->content[0] == '<')
	{
		j = data->execs[data->exec_count]->input_written;
		while(current && j < (data->execs[data->exec_count]->input_written + 2))
		{
			if(!current)
				exit(2);
			data->execs[data->exec_count]->input[j] = ft_strdup(current->content);
			current = current->next;
			j++;
		}
		data->execs[data->exec_count]->input_written += 2;
	}
	else
	{
		j = data->execs[data->exec_count]->output_written;
		while(current && j < (data->execs[data->exec_count]->output_written + 2))
		{
			if(!current)
				exit(2);
			//ft_printf("current content is %s\n", current->content);
			data->execs[data->exec_count]->output[j] = ft_strdup(current->content);
			current = current->next;
			j++;
		}
		data->execs[data->exec_count]->output_written += 2;
	}
	return (current);
}

t_token	*write_args(t_data *data, t_token *current)
{
	if(current->content)
		data->execs[data->exec_count]->args[data->arg_count] = ft_strdup(current->content);
	data->arg_count++;
	current = current->next;
	return(current);
}

void get_command(t_data *data)
{
	int i;

	i = 0;
	if (!data->execs[data->exec_count]->args[0])
		data->execs[data->exec_count]->command = NULL;
	else
	{
		while(data->execs[data->exec_count]->args[0][i])
		{
			data->execs[data->exec_count]->args[0][i] = ft_tolower(data->execs[data->exec_count]->args[0][i]);
			i++;
		}
		if (is_built_in(data->execs[data->exec_count]->args[0]))
			data->execs[data->exec_count]->command = ft_strdup(data->execs[data->exec_count]->args[0]);
		else
		{
			data->execs[data->exec_count]->command = get_path(data->execs[data->exec_count]->args[0]);
			if(!data->execs[data->exec_count]->command)
				data->execs[data->exec_count]->command = ft_strdup(data->execs[data->exec_count]->args[0]);
		}
	}
}


int parse_tokens(t_data *data)
{
	t_token *current;

	if(data->tokens)
		current = data->tokens;
	data->execs = malloc(sizeof(t_exec *) * (get_exec_count(data->tokens) + 1));
	if (!data->execs)
		return(0);
	data->execs[get_exec_count(data->tokens)] = NULL;
	if(!syntax(data))
		return(g_errno = 2, 0);
	printf("after syntax\n");
	while (current)
	{
		init_exec(data, current);
		if(data->pipeflag)
			write_pipe_in(data);
		while (current && current->type != is_pipe)
		{
			if (current && current->type == redirection)
				current = write_redirection(data, current);
			else if (current && current->type == word)
				current = write_args(data, current);
		}
		get_command(data);
		if (current && current->type == is_pipe)
			current = write_pipe_out(data, current);
	}
	free_tokens(data);
	return(1);
}
