#include "../include/minishell.h"

	
void freestrings(char *s1, char *s2, char *s3, char **array)
{
	printf("in free strings\n");
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
	if (array)
		ft_free2d(array);
}

int is_char(char place, char c)
{
	if (place == c)
		return (1);
	return (0);
}

void switch_flag(int *flag)
{
	if (*flag == 0)
		*flag = 1;
	else if (*flag == 1)
		*flag = 0;
}

void print_tokens (t_token **token)
{
	t_token *current;

	current = *token;
	while (current)
	{
		ft_printf("Token-Content: %s\n", current->content);
		ft_printf("Token-Type: %d\n", current->type);
		ft_printf("\n", current->type);
		current = current->next;
	}
}

void free_tokens(t_data *data, t_free_options type)
{
	t_token	*current;
	t_token	*tmp;

	if(data->tokens)
	{
		current = data->tokens;
		while(current)
		{
			tmp = current->next;
			if (type == everything)
				free(current->content);
			free(current);
			current = tmp;
		}
	}
}

void free_exec(t_data *data)
{
	int	i;

	i = 0;
	while(data->execs[i])
	{
		free(data->execs[i]->args);
		free(data->execs[i]->input);
		free(data->execs[i]->output);
		free(data->execs[i]);
		i++;
	}
	free(data->execs);
}

void free_data(t_data *data)
{
	free_exec(data);
	if(data->execs)
		free(data->execs);
	if(data)
		free(data);
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data, int args, char **argv)
{
	data->tokens = NULL;
	data->execs = NULL;
	data->pipeflag = 0;
	data->arg_count = 0;
	data->exec_count = 0;
	args = 99999;
	argv = NULL;
}

void	printtokens(t_exec **exec)
{
	int	i = 0;
	int	n = 0;
	while (exec[i])
	{
		printf("\nEXEC[%d]\n", i);
		printf("---------------------------------------------\n");
		printf("Command:	%s\n", exec[i]->command);
		printf("Input:	\n");
		while (exec[i]->input[n])
		{
			printf("- input[%d]:	%s\n", n, exec[i]->input[n]);
			n++;
		}
		if (exec[i]->input[0] == NULL)
			printf("%s\n", NULL);
		n = 0;
		printf("Arguments:	\n");
		while (exec[i]->args[n])
		{
			printf("- arg[%d]:	%s\n", n, exec[i]->args[n]);
			n++;
		}
		n = 0;
		printf("Output: \n");
		while (exec[i]->output[n])
		{
			printf("- output[%d]:	%s\n", n, exec[i]->output[n]);
			n++;
		}
		if (exec[i]->output[0] == NULL)
			printf("%s\n", NULL);
		i++;
		printf("---------------------------------------------\n");
	}
}