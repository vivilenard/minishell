/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 11:27:05 by vlenard           #+#    #+#             */
/*   Updated: 2023/02/05 20:55:57 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_howmanyc(char *s, char c, int count, int flag)
{
	while (s[count] == c)
	{
		count++;
		flag++;
	}
	if (s[count] == '\0')
		return (-1);
	return (flag);
}

int	ft_countstrs(char *s, char c)
{
	int	i;
	int	count;
	int	flag;

	i = 0;
	count = 0;
	flag = 0;
	while (s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		flag = ft_howmanyc(s, c, i, 0);
		if (flag > 0)
		{
			count++;
			i = i + flag;
		}
		else if (flag == 0)
			i++;
		else if (flag < 0)
			return (count + 1);
	}
	return (count + 1);
}

int	ft_flag(int c, char *strbuff1)
{
	int	count;
	int	flag;

	count = 0;
	flag = -1;
	while (strbuff1[count] != '\0')
	{
		if (strbuff1[count] == c)
		{
			flag = ft_howmanyc(strbuff1, c, count, 0);
			break ;
		}
		count++;
	}
	return (flag);
}

void	ft_assignstrs(char *strbuff, char **split, int c, int start)
{
	int		flag;
	int		n;
	char	*strbuff1;
	int		i;

	n = 0;
	flag = 1;
	while (flag > 0)
	{
		strbuff1 = ft_strdup(strbuff + start);
		free (strbuff);
		i = 0;
		while (strbuff1[i] != c && strbuff1[i] != '\0')
			i++;
		split[n] = malloc((i + 1) * sizeof(char));
		ft_strlcpy(split[n], strbuff1, i + 1);
		flag = ft_flag(c, strbuff1);
		start = i + flag;
		strbuff = strbuff1;
		n++;
	}
	if (flag < 0)
		free (strbuff1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	char	*strbuff;
	int		i;
	int		strcount;

	i = 0;
	if (c != '\0' && !s)
		return (NULL);
	strcount = ft_countstrs((char *)s, c);
	if (c == '\0' && s[0] == '\0')
		strcount = 0;
	split = malloc((strcount + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (strcount > 0)
	{
		while (s[i] == c)
			i++;
		strbuff = ft_strdup(s + i);
		ft_assignstrs(strbuff, split, c, 0);
	}
	split[strcount] = 0;
	return (split);
}
