/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 10:18:04 by mgraefen          #+#    #+#             */
/*   Updated: 2023/02/17 14:40:51 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Splits at whitespaces and redirections signs. Until the function encounters
a null terminator or Pipe-Sign.

When encountering a redirection sign the token will be flagged with the
corresponding redirection sign.

If "echo" is encountered everything after the option is saved into one string
until the function finds a redirection, pipe or NULL.

If " or ' is encountered, the function does not split until another " or '
is present in the string.

The function then continues */

#include "../include/minishell.h"

void split_into_tokens(t_data data, char *str)
{
	int	i;

	i = 0;
	while(str[i] || str[i] != '|')
	{
		if(str[i] == '<' || str[i] == '>' )
		
		i++;
	}
}