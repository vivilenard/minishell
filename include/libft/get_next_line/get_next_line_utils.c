/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 15:35:51 by vlenard           #+#    #+#             */
/*   Updated: 2023/01/30 09:01:51 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	n;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s2)
		return (NULL);
	str = malloc((ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	n = 0;
	while (s1[i])
		str[i++] = s1[n++];
	n = 0;
	while (s2[n])
		str[i++] = s2[n++];
	str[i] = '\0';
	return (free (s1), free (s2), str);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char) c;
	i = 0;
	if (!s)
		return (0);
	if (s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i] == uc)
			return ((char *)s + i);
		i++;
	}
	if (uc == s[i])
		return ((char *)s + i);
	return (0);
}

char	*ft_strdup_gnl(char *s)
{
	size_t	i;
	size_t	len;
	char	*scpy;

	i = 0;
	len = ft_strlen_gnl(s);
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
