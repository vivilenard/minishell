#include "../../include/minishell.h"

void	write_pipe_in(t_data *data)
{
	int	i;

	i = data->execs[data->exec_count]->input_written;
	data->execs[data->exec_count]->input[i] = ft_strdup("|");
	data->pipeflag = 0;
	data->execs[data->exec_count]->input_written++;
}

t_token	*write_pipe_out(t_data *data, t_token *current)
{
	int	i;

	i = data->execs[data->exec_count]->output_written;
	data->execs[data->exec_count]->output[i] = ft_strdup(current->content);
	data->execs[data->exec_count]->output_written++;
	current = current->next;
	data->pipeflag = 1;
	data->arg_count = 0;
	data->exec_count++;
	return (current);
}

int	is_inquotes(char *str)
{
	if (str && ft_strlen(str) > 2)
	{
		if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
			return (1);
		else if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
			return (1);
	}
	return (0);
}
