#include "../include/minishell.h"

void init_exec(t_exec *exec, int arg_count)
{
	exec->args = NULL;
	exec->input = NULL;
	exec->output = NULL;
	exec->command = NULL;
	exec->args = malloc((sizeof(char *) * (arg_count + 1)));
	exec->input = (char **) malloc((sizeof(char *) * 2) + 1);
	exec->output = (char **) malloc((sizeof(char *) * 2) + 1);
}

t_token	*write_redirection(t_token *current, t_exec *exec)
{
	int	j;

	j = 0;
	if(current->content[0] == '<')
	{
		while(j < 2)
		{
			exec->input[j] = current->content;
			current = current->next;
			j++;
		}
		exec->input[j] = NULL;
	}
	else
	{
		while(j < 2)
		{
			exec->output[j] = current->content;
			current = current->next;
			j++;
		}
		exec->output[j] = NULL;
	}
	return (current);
}

t_token	*write_pipe(t_exec *exec, t_token *current)
{
	exec->output[0] = current->content;
	exec->output[1] = NULL;
	current = current->next;
	return(current);
}

int parse_tokens(t_data *data)
{
	t_token *current;
	int		exec_count;
	int		arg_count;

	arg_count = 0;
	exec_count = 0;
	data->pipeflag = 0;
	if(data->tokens)
		current = data->tokens;
	data->execs = ft_calloc(sizeof(t_exec *), get_exec_count(data->tokens) + 1);
	if (!data->execs)
		return(1);
	while (current)
	{
		data->execs[exec_count] = malloc(sizeof(t_exec));
		init_exec(data->execs[exec_count], get_arg_num(current));
		//printf("%i", get_arg_num(current));
		if(data->pipeflag)
		{
			data->execs[exec_count]->input[0] = "|";
			data->execs[exec_count]->input[1] = NULL;
		}
		while (current && current->type != is_pipe)
		{
			if (current->type == redirection)
				current = write_redirection(current, data->execs[exec_count]);
			else if (current && (current->type == word || current->type == option))
			{
				data->execs[exec_count]->args[arg_count] = current->content;
				arg_count++;
				current = current->next;
			}
		}
		data->execs[exec_count]->command = get_path(data->execs[exec_count]->args[0]);
		data->execs[exec_count]->args[arg_count] = NULL;
		if (current && current->type == is_pipe)
		{
			current = write_pipe(data->execs[exec_count], current);
			data->pipeflag = 1;
			exec_count++;
			arg_count = 0;
		}
		else
		{
			data->execs[exec_count]->output[0] = NULL;
			data->execs[exec_count]->output[1] = NULL;
		}
	}
	data->execs[exec_count + 1] = NULL;
	free_tokens(data, only_tokens);
	//print_execs(data);
	return(0);
}
