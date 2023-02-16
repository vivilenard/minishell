/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 19:57:46 by vlenard           #+#    #+#             */
/*   Updated: 2022/12/20 16:36:48 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putandcountstr(char *str, int print_length)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
		print_length++;
	}
	return (print_length);
}

int	ft_lookforpercent(const char *s, va_list args, int print_length)
{
	int		i;
	int		start;
	char	*subs;

	i = 0;
	start = 0;
	while (i <= (int)ft_strlen(s))
	{
		if (s[i] == '%' || s[i] == '\0')
		{
			subs = ft_substr(s, start, i - start);
			if (subs)
			{
				print_length = ft_putandcountstr(subs, print_length);
				free (subs);
			}
			if (s[i] == '\0')
				return (print_length);
			print_length = print_length + ft_takearg(s, i, args);
			i++;
			start = i + 1;
		}
		i++;
	}
	return (print_length);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		print_length;

	print_length = 0;
	va_start(args, s);
	print_length = ft_lookforpercent(s, args, print_length);
	va_end(args);
	return (print_length);
}
