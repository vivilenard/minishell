/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:33:24 by vlenard           #+#    #+#             */
/*   Updated: 2022/10/30 15:34:32 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*m;

	i = 0;
	m = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (!m)
		return (NULL);
	while (s[i] != '\0')
	{
		m[i] = f(i, s[i]);
		i++;
	}
	m[ft_strlen(s)] = '\0';
	return (m);
}
