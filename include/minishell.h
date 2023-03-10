/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:21:04 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/16 19:50:18 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include "libft/libft.h"

typedef struct s_token
{
	char	*content;
	int		a;
	//enum	token;
}				t_token;

char	*prompt(void);
char	*username(void);
void	freestrings(char *s1, char *s2, char *s3, char **array);
t_token	*lexer(char *input);

#endif