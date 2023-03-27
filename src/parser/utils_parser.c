#include "../../include/minishell.h"

void print_execs(t_data *data)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while(data->execs[i])
	{
		ft_printf("EXEC #%i\n", i);
		ft_printf("-------------------\n");
		while(data->execs[i]->input[j])
		{
			ft_printf("INPUT %i: %s\n", j, data->execs[i]->input[j]);
			j++;
		}
		ft_printf("-------------------\n");
		ft_printf("COMMAND:\n");
		ft_printf("%s\n", data->execs[i]->command);
		ft_printf("ARGS:\n");
		j = 0;
		while(data->execs[i]->args[j])
		{
			ft_printf("ARG #%i: %s\n", j, data->execs[i]->args[j]);
			j++;
		}
		ft_printf("-------------------\n");
		j = 0;
		while(data->execs[i]->output[j])
		{
			ft_printf("OUTPUT %i: %s\n", j, data->execs[i]->output[j]);
			j++;
		}
		ft_printf("\n");
		ft_printf("\n");
		j = 0;
		i++;
	}
}

int	get_exec_count(t_token	*current)
{
	int		exec_count;

	if(!current)
		exec_count = 0;
	else
		exec_count = 1;
	while (current != NULL && current->content)
	{
		if (current->type == is_pipe)
			exec_count++;
		current = current->next;
	}
	//ft_printf("EXEC Count is: %i \n", exec_count);
	return (exec_count);
}

int get_output_num(t_token *current)
{
	t_token *tmp;
	int		count;

	count = 0;
	tmp = current;
	while(tmp && tmp->type != is_pipe)
	{
		if(tmp->type == redirection && tmp->content[0] == '>')
			count++;
		tmp = tmp->next;
	}
	return(count);
}

int get_input_num(t_token *current)
{
	t_token *tmp;
	int		count;

	count = 0;
	tmp = current;
	while(tmp && tmp->type != is_pipe)
	{
		if(tmp->type == redirection && tmp->content[0] == '<')
			count++;
		tmp = tmp->next;
	}
	return(count);
}

int exec_has_pipe(t_token *current)
{
	t_token *tmp;

	tmp = current;
	while (tmp)
	{
		if (tmp->type == is_pipe)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	get_arg_num(t_token *current)
{
	t_token	*tmp;
	int		arg_count;
	int		red_count;

	tmp = NULL;
	red_count = 0;
	arg_count = 0;
	tmp = current;
	while (tmp && tmp->type != is_pipe)
	{
		if(tmp->type == redirection)
			red_count ++;
		arg_count++;
		tmp = tmp->next;
	}
	return(arg_count - (red_count * 2));
}

void	write_pipe_in(t_data *data)
{
	int i;

	i = data->execs[data->exec_count]->input_written;
	data->execs[data->exec_count]->input[i] = ft_strdup("|");
	data->pipeflag = 0;
	data->execs[data->exec_count]->input_written++;
}

t_token	*write_pipe_out(t_data *data, t_token *current)
{
	int i;

	i = data->execs[data->exec_count]->output_written;
	
	data->execs[data->exec_count]->output[i] = ft_strdup(current->content);
	data->execs[data->exec_count]->output_written++;
	current = current->next;
	data->pipeflag = 1;
	data->arg_count = 0;
	data->exec_count++;
	return(current);
}