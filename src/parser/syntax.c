#include "../../include/minishell.h"

void	print_syntaxerror_s(char *s)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(s, 2);
	ft_putendl_fd("'", 2);
}
void	print_syntaxerror_c(char c)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
	write(1, &c, 1);
	ft_putendl_fd("'", 2);
}

int	ft_count_char(char *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while(s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}
int syntax(t_data *data)
{
	t_token	*current;
	//print_tokens(&data->tokens);

	current = data->tokens;
	if (current->type == is_pipe)
		return(print_syntaxerror_s("|"), 0);
	while(current)
	{
		if (current->type == redirection && ft_haystack(current->content, "<")
			&& ft_haystack(current->content, ">"))
			return (print_syntaxerror_s("\\n"), 0);
		if (current->type == redirection && ft_count_char(current->content, '<') > 2)
			return (print_syntaxerror_c(current->content[0]), 0);
		if (current->type == redirection && ft_count_char(current->content, '>') > 2)
			return (print_syntaxerror_c(current->content[0]), 0);
		if (current->type == redirection && ft_haystack(current->content, " "))
			return (print_syntaxerror_c(current->content[0]), 0);
		// if (current->type == word && ft_strncmp(current->content, ".", 2) == 0)
		// 	return (ft_putendl_fd("filename argument required", 2), 0);
		if (!current->next && current->type == is_pipe)
			return(print_syntaxerror_s("|"), 0);
		if (!current->next && current->type == redirection)
			return (print_syntaxerror_s("\\n"), 0);
		current = current->next;
	}
	return (1);
}

// int check_syntax(t_data *data)
// {
// 	t_token	*current;

// 	current = data->tokens;
// 	if(current->type == is_pipe)
// 		return(0);
// 	while(current)
// 	{
// 		if(current->type == redirection && (!current->next || current->next->type != word))
// 		{
// 			ft_putstr_fd("syntax error near unexpected token `", 2);
// 			if (ft_strlen(current->content) == 3)
// 				write(2, &current->content[2], 1);
// 			else if (ft_strlen(current->content) > 3)
// 				write(2, &current->content[3], 1);
// 			else if(!current->next)
// 				ft_putstr_fd("newline", 2);
// 			else
// 				ft_putstr_fd(current->content, 2);
// 			ft_putendl_fd("'", 2);
// 			return (0);
// 		}
// 		if(current->type == redirection && ft_strlen(current->content) >= 2)
// 		{
// 			ft_putstr_fd("syntax error near unexpected token `", 2);
// 			ft_putstr_fd(current->content, 2);
// 			ft_putendl_fd("'", 2);
// 			return(0);
// 		}
// 		if(!ft_strncmp(current->content, "echo", 5) && current->next && current->next->type == redirection)
// 			return(0);
// 		if(!ft_strncmp(current->content, "echo", 5) && current->next && current->next->type == is_pipe)
// 		{
// 			return(0);
// 		}
// 		if(current->type == is_pipe && current->next && current->next->type != word)
// 		{
// 			ft_putstr_fd("syntax error near unexpected token `", 2);
// 			ft_putstr_fd(current->content, 2);
// 			ft_putendl_fd("'", 2);
// 			return(0);
// 		}
// 		current = current->next;
// 	}
// 	return(1);
// }