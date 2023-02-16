/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 10:53:00 by vlenard           #+#    #+#             */
/*   Updated: 2022/11/03 17:08:14 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		n;
	int		i;
	char	*str;

	n = 0;
	while (s1[n] != '\0')
	{
		if (ft_strchr(set, s1[n]) == 0)
			break ;
		n++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i--;
	}
	str = ft_substr((char *)s1, n, (i + 1) - n);
	return (str);
}
