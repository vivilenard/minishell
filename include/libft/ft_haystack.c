/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_haystack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:20:12 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/23 19:04:20 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_haystack(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	if (ft_strlen(needle) == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		n = 0;
		while (haystack[i + n] == needle[0 + n]
			&& (haystack[i + n] != '\0'))
		{
			if (needle[0 + n + 1] == '\0')
				return (((char *)haystack + i));
			n++;
		}
		i++;
	}
	return (NULL);
}
