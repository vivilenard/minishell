#include "../include/minishell.h"

void freestrings(char *s1, char *s2, char *s3, char **array)
{
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

void free_tokens(t_token **token, t_free_options type)
{
	int	i;

	i = 0;
	while(token[i])
	{
		if (type == everything)
			if(token[i]->content)
				free(token[i]->content);
		free(token[i]);
		i++;
	}
}

void free_data(t_data *data)
{
	free_tokens(data->tokens, everything);
	if(data->tokens)
		free(data->tokens);
	if(data)
		free(data);
	exit(EXIT_FAILURE);
}

void	init_data(t_data *data)
{
	data->token_count = 0;
}
