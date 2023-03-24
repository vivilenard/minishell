
#include "../../include/minishell.h"

int	is_outer(char *str, char c)
{
	if(str[0] == c && str[ft_strlen(str) - 1] == c)
		return (1);
	return (0);
}

char *cut_outer_quotes(char *str)
{
	char	*out;
	char	*tmp;
	char	c;

	c = '\0';
	tmp = str;
	out = str;
	if(!is_outer(str, '\'') && !is_outer(str, '\"'))
		return(str);
	if(is_outer(str, '\''))
		c = '\'';
	else if(is_outer(str, '\"'))
		c = '\"';
	while(is_outer(out, c))
	{
		out = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
		free(tmp);
		tmp = out;
	}
	return(out);
}

t_token	*ft_new_token(char *str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->content = NULL;
	if (str)
		new_token->content = ft_strdup(str);
	new_token->next = NULL;
	new_token->type = content_analyse(new_token);
	// if(new_token->type == word)
	// 	new_token->content = cut_outer_quotes(new_token->content);
	return (new_token);
}

t_token	*ft_token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_token_add_back(t_token **tokens, t_token *new)
{
	t_token	*end;

	if (!new)
		return ;
	if (*tokens)
	{
		end = ft_token_last(*tokens);
		end->next = new;
	}
	else
		*tokens = new;
}

int	init_token(t_token **tokens, char *str)
{
	t_token	*temp;

	temp = NULL;
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
	data->tokens = NULL;
	while(split_tokens[i])
	{
		if(init_token(&data->tokens, split_tokens[i]))
			return(ft_free2d(split_tokens), 0);
		i++;
	}
	if(split_tokens)
		ft_free2d(split_tokens);
	return (1);
}
