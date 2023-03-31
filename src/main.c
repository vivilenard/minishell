#include "../include/minishell.h"

void	put_new_promptline(void)
{
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	take_input(char **input, char *promptline)
{
	if (isatty(0))
		*input = readline(promptline);
	else
		*input = get_next_line(0);
	if (!*input)
		return (0);
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (1);
}

int	g_errno = 0;

void	printtokens(t_exec **exec)
{
	int	i = 0;
	int	n = 0;
	while (exec && exec[i])
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
			printf("%s\n", (char *)NULL);
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
			printf("%s\n", (char *)NULL);
		i++;
		printf("---------------------------------------------\n");
	}
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
int	main(int args, char **argv, char **env)
{
	char	*input;
	t_data	*data;

	data = init_data(env, args, argv);
	while (1)
	{
		signals();
		reset_data(data);
		if (!take_input(&input, data->promptline))
			break ;
		if (ft_strncmp(input, "", 1) == 0)
			continue ;
		if (!lexer(input, data))
			continue ;
		//print_tokens(&data->tokens);
		if (!parse_tokens(data))
			continue ;
		//printtokens(data->execs);
		//print_execs(data);
		if (!expander(data->execs, data->env))
			continue ;
		//printf("hi\n");
		//printtokens(data->execs);
		executer(data);
		free_exec(data, input);
	}
	free_data(data);
	//system ("leaks minishell");
	return (g_errno);
}
