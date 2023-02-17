/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:32:19 by mgraefen          #+#    #+#             */
/*   Updated: 2023/02/17 14:07:02 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main (void)
{
	char *input;
	char *promptline;

	promptline = prompt();
	while (1)
		input = readline(promptline);
	freestrings(input, promptline, NULL, NULL);
	return (0);
}