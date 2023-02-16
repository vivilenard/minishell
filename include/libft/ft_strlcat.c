/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:09:52 by vlenard           #+#    #+#             */
/*   Updated: 2022/11/04 12:28:22 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	idst;
	size_t	initialdstsize;
	size_t	i;

	initialdstsize = ft_strlen(dst);
	idst = ft_strlen(dst);
	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize <= initialdstsize)
		return (dstsize + ft_strlen(src));
	while (idst < dstsize - 1 && src[i])
	{
		dst[idst] = src[i];
		idst++;
		i++;
	}
	dst[idst] = '\0';
	return (initialdstsize + ft_strlen(src));
}
