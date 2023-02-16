/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:28:24 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/16 17:03:22 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char *username()
{
	return (getenv("USER"));
}

char *prompt()
{
	char	*user;
	char	*prompt;
	
	user = username();
	prompt = ft_strjoinwithoutfree(user, "@minishell♥ ");
	return (prompt);
}
