#include "../../include/minishell.h"

void	init_exec(t_data *data, t_token *current)
{
	data->execs[data->exec_count] = malloc (sizeof(t_exec) + 1);
	data->execs[data->exec_count]->pipe_num = exec_has_pipe(current);
	data->execs[data->exec_count]->input_num = get_input_num(current)
		* 2 + data->pipeflag;
	data->execs[data->exec_count]->output_num = get_output_num(current)
		* 2 + data->execs[data->exec_count]->pipe_num;
	data->execs[data->exec_count]->arg_num = get_arg_num(current);
	data->execs[data->exec_count]->input_written = 0;
	data->execs[data->exec_count]->output_written = 0;
	data->execs[data->exec_count]->command = NULL;
	data->execs[data->exec_count]->args = (char **) malloc(sizeof(char *)
			* (data->execs[data->exec_count]->arg_num + 1));
	data->execs[data->exec_count]
		->args[data->execs[data->exec_count]->arg_num] = NULL;
	data->execs[data->exec_count]->input = (char **) malloc(sizeof(char *)
			* (data->execs[data->exec_count]->input_num + data->pipeflag + 1));
	data->execs[data->exec_count]
		->input[data->execs[data->exec_count]->input_num] = NULL;
	data->execs[data->exec_count]->output = (char **) malloc(sizeof(char *)
			* (data->execs[data->exec_count]->output_num + 1));
	data->execs[data->exec_count]
		->output[data->execs[data->exec_count]->output_num] = NULL;
}

t_token	*process_token(t_data *data, t_token *current)
{
	init_exec(data, current);
	if (data->pipeflag)
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
	return (current);
}

int	parse_tokens(t_data *data)
{
	t_token	*current;

	if (data->tokens)
		current = data->tokens;
	data->execs = malloc(sizeof(t_exec *) * (get_exec_count(data->tokens) + 1));
	if (!data->execs)
		return (0);
	data->execs[get_exec_count(data->tokens)] = NULL;
	if (!syntax(data))
		return (g_errno = 2, 0);
	while (current)
		current = process_token(data, current);
	free_tokens(data);
	return (1);
}
