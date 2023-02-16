/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:37:13 by vlenard           #+#    #+#             */
/*   Updated: 2022/11/07 18:54:28 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	ci;

	ci = c;
	i = 0;
	while (i < n)
	{	
		if (((unsigned char *) s)[i] == ci)
			return ((unsigned char *) s + i);
		i++;
	}
	return (NULL);
}
