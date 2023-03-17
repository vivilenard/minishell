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
	data->execs[data->exec_count]->args = (char **) ft_calloc(sizeof(char *),
	 data->execs[data->exec_count]->arg_num + 1);
	data->execs[data->exec_count]->input = (char **) ft_calloc(sizeof(char *),
	 data->execs[data->exec_count]->input_num + data->pipeflag + 1);
	data->execs[data->exec_count]->output = (char **) ft_calloc(sizeof(char *),
	 data->execs[data->exec_count]->output_num + 1);
}

t_token	*write_redirection(t_data *data, t_token *current)
{
	int	j;

	if(current->content[0] == '<')
	{
		j = data->execs[data->exec_count]->input_written;
		while(j < (data->execs[data->exec_count]->input_written + 2))
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
		while(j < (data->execs[data->exec_count]->output_written + 2))
		{
			if(!current)
				exit(2);
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
	data->execs[data->exec_count]->args[data->arg_count] = ft_strdup(current->content);
	data->arg_count++;
	current = current->next;
	return(current);
}

void get_command(t_data *data)
{
	if (is_built_in(data->execs[data->exec_count]->args[0]))
		data->execs[data->exec_count]->command = ft_strdup(data->execs[data->exec_count]->args[0]);
	else
	{
		data->execs[data->exec_count]->command = get_path(data->execs[data->exec_count]->args[0]);
		if(!data->execs[data->exec_count]->command)
			data->execs[data->exec_count]->command = ft_strdup(data->execs[data->exec_count]->args[0]);
	}
}

int check_syntax(t_data *data)
{
	t_token	*current;

	current = data->tokens;
	if(current->type == is_pipe)
		exit(2);
	while(current)
	{
		if(current->type == redirection && !current->next)
			exit(2);
		if(current->type == redirection && current->next->type == redirection)
			exit(2);
		if(current->type == redirection && ft_strlen(current->content) > 2)
			exit(2);
		if(!ft_strncmp(current->content, "echo", 5) && current->next->type == redirection)
			exit(2);
		if(!ft_strncmp(current->content, "echo", 5) && current->next->type == is_pipe)
			exit(2);
		if(current->type == is_pipe && current->next->type != word)
			exit(2);
		current = current->next;
	}
	return(0);
}

int parse_tokens(t_data *data)
{
	t_token *current;

	if(data->tokens)
		current = data->tokens;
	data->execs = ft_calloc(sizeof(t_exec *), get_exec_count(data->tokens) + 1);
	if (!data->execs)
		return(0);
	check_syntax(data);
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
