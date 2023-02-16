/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:45:19 by vlenard           #+#    #+#             */
/*   Updated: 2022/10/27 11:45:19 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*scpy;

	i = 0;
	len = ft_strlen(s);
	scpy = (char *)malloc((len + 1) * sizeof(char));
	if (!scpy)
		return (NULL);
	while (i < len)
	{
		*(scpy + i) = *(s + i);
		i++;
	}
	if (i == len)
		*(scpy + i) = *(s + i);
	return (scpy);
}
