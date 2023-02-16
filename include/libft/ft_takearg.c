/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_takearg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:49:29 by vlenard           #+#    #+#             */
/*   Updated: 2022/12/20 16:37:11 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//partof printf
#include "libft.h"

int	ft_isu(va_list args, int ch, int print_length)
{
	char	*s;

	ch = (unsigned int)ch;
	ch = va_arg(args, unsigned int);
	s = ft_utoa(ch);
	print_length = ft_putandcountstr(s, print_length);
	free(s);
	return (print_length);
}

int	ft_isdi(va_list args, int print_length)
{
	char	*s;
	int		n;

	n = va_arg(args, int);
	s = ft_itoa(n);
	print_length = ft_putandcountstr(s, print_length);
	free(s);
	return (print_length);
}

int	ft_isc(va_list args, char ch, int print_length)
{
	ch = va_arg(args, int);
	write(1, &ch, 1);
	print_length++;
	return (print_length);
}

int	ft_ispercent(char ch, int print_length)
{
	write(1, &ch, 1);
	print_length++;
	return (print_length);
}

int	ft_takearg(const char *s, int i, va_list args)
{
	int	ch;
	int	print_length;

	print_length = 0;
	i++;
	ch = '%';
	if (((char *)s)[i] == 'd' || ((char *)s)[i] == 'i')
		return (ft_isdi(args, print_length));
	if (((char *)s)[i] == 'c')
		return (ft_isc(args, ch, print_length));
	if (((char *)s)[i] == 's')
		return (ft_iss(args, print_length));
	if (((char *)s)[i] == 'X')
		return (ft_isbigx(args, print_length));
	if (((char *)s)[i] == 'x')
		return (ft_isx(args, print_length));
	if (((char *)s)[i] == 'u')
		return (ft_isu(args, ch, print_length));
	if (((char *)s)[i] == '%')
		return (ft_ispercent(ch, print_length));
	if (((char *)s)[i] == 'p')
		return (ft_ispointer(args, print_length));
	return (print_length);
}
