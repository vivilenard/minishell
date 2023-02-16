/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:33:45 by vlenard           #+#    #+#             */
/*   Updated: 2022/11/04 12:32:56 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_truelen(char const *s, unsigned int start, size_t len)
{
	size_t	truelen;

	truelen = 0;
	while (s[start])
	{
		start++;
		truelen++;
	}
	if (truelen < len)
		return (truelen);
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	ss = malloc((ft_truelen(s, start, len) + 1) * sizeof(char));
	if (ss == NULL)
		return (NULL);
	i = 0;
	while (i < ft_truelen(s, start, len)
		&& s[i] != '\0' && start < ft_strlen(s))
	{
		ss[i] = s[start + i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}
