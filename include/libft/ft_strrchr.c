/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 14:32:05 by vlenard           #+#    #+#             */
/*   Updated: 2022/10/21 15:17:26 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	uc;

	uc = (unsigned char) c;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (*(s + len) == uc)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}
