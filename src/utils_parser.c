#include "../include/minishell.h"

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
		ft_printf("INPUT-TYPE: %s\n", data->execs[i]->input[0]);
		if(data->execs[i]->input[1])
			ft_printf("INPUT-SOURCE: %s\n", data->execs[i]->input[1]);
		ft_printf("-------------------\n");
		ft_printf("COMMAND:\n");
		ft_printf("%s\n", data->execs[i]->command);
		ft_printf("ARGS:\n");
		while(data->execs[i]->args[j])
		{
			ft_printf("ARG #%i: %s\n", j, data->execs[i]->args[j]);
			j++;
		}
		ft_printf("-------------------\n");
		if(data->execs[i]->output[0])
			ft_printf("OUTPUT-TYPE: %s\n", data->execs[i]->output[0]);
		if(data->execs[i]->output[1])
			ft_printf("OUTPUT-SOURCE: %s\n", data->execs[i]->output[1]);
		ft_printf("\n");
		ft_printf("\n");
		j = 0;
		i++;
	}
}

int	get_exec_count(t_token	*current)
{
	int		exec_count;

	exec_count = 1;
	while (current != NULL && current->content)
	{
		if (current->type == is_pipe)
			exec_count++;
		current = current->next;
	}
		return (exec_count);
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
		ft_printf("in ARG-LOOP %i\n", arg_count);
		if(tmp->type == redirection)
			red_count ++;
		arg_count++;
		tmp = tmp->next;
	}
	return(arg_count - (red_count * 2));
}