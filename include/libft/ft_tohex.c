/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tohex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:59:34 by vlenard           #+#    #+#             */
/*   Updated: 2022/12/20 16:37:01 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_converttocharacter(unsigned int n, char c)
{
	unsigned int	i;

	if (n >= 10)
	{
		i = 10;
		if (c == 'X')
			c = 'A';
		else if (c == 'x')
			c = 'a';
		while (i < 16)
		{
			if (i == n)
				break ;
			c++;
			i++;
		}
	}
	else
	{
		c = n + '0';
	}
	return (c);
}

int	ft_countstr(unsigned int d)
{
	unsigned int	count;

	count = 1;
	while ((d / 16) > 0)
	{
		d = d / 16;
		count++;
	}
	return (count);
}

char	*ft_tohex(unsigned int d, char c)
{
	unsigned int	strlen;
	char			*str;

	strlen = ft_countstr(d);
	str = (char *)malloc((ft_countstr(d) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[strlen] = '\0';
	strlen--;
	while (d >= 16 && strlen > 0)
	{
		str[strlen] = ft_converttocharacter(d % 16, c);
		d = d / 16;
		strlen--;
	}
	str[0] = ft_converttocharacter(d, c);
	return (str);
}
