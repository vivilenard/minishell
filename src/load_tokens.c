
#include "../include/minishell.h"

t_token	*ft_new_token(char *str)
{
	t_token	*new_token;

	new_token = NULL;
	if (str)
	{
		new_token = (t_token *) malloc(sizeof(t_token));
		if (!new_token)
			return (0);
		new_token->content = str;
		new_token->type = content_analyse(new_token);
		new_token->next = NULL;
	}
	return (new_token);
}

t_token	*ft_token_last(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (!tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void	ft_token_add_back(t_token **tokens, t_token *new)
{
	t_token	*tmp;

	if (!tokens || !*tokens)
		*tokens = new;
	else
	{
		tmp = ft_token_last(*tokens);
		if (tmp)
			tmp->next = new;
	}
}

int	init_token(t_token **tokens, char *str)
{
	t_token	*temp;

	temp = ft_new_token(str);
	if (!temp)
		return (1);
	ft_token_add_back(tokens, temp);
	return (0);
}

int load_tokens(char **split_tokens, t_data *data)
{
	int	i;
	i = 0;
	data->tokens = malloc(sizeof(t_token **));
	while(split_tokens[i])
	{
		if(init_token(data->tokens, split_tokens[i]))
			return(1);
		i++;
	}
	data->token_count = i;
	free(split_tokens);
	//print_tokens(data->tokens);
	return (0);
}
