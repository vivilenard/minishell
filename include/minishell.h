/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgraefen <mgraefen@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:56:41 by mgraefen          #+#    #+#             */
/*   Updated: 2023/02/17 10:47:54 by mgraefen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "../Libft/libft.h"
# include <sys/wait.h>

/* Data contains all the data of one input. This input is divided by prompts
(one prompt could be piped into another). Every Prompt is divided into tokens.
Every token has a tokentype */

typedef enum e_tokentype
{
	word,
	option,
	value,
}	t_tokentype;


typedef struct s_token
{
	char		*content;
	t_tokentype	token;
}				t_token;

typedef struct s_string
{
	t_token *tokens;
	char	*input;
	char	*output;
}	t_string;

typedef struct s_data
{
	t_string *strings;
}	t_data;


int	main (void);


#endif
