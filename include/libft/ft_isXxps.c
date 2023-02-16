/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isXxps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:42:32 by vlenard           #+#    #+#             */
/*   Updated: 2022/12/20 16:38:09 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isbigx(va_list args, int print_length)
{
	char	*str;

	str = ft_tohex(va_arg(args, unsigned int), 'X');
	print_length = ft_putandcountstr(str, print_length);
	free (str);
	return (print_length);
}

int	ft_isx(va_list args, int print_length)
{
	char			*str;
	unsigned int	n;

	n = va_arg(args, unsigned int);
	str = ft_tohex(n, 'x');
	print_length = ft_putandcountstr(str, print_length);
	free (str);
	return (print_length);
}

int	ft_ispointer(va_list args, int print_length)
{
	char	*str;

	str = ft_ultopointer(va_arg(args, unsigned long int));
	print_length = ft_putandcountstr(str, print_length);
	free(str);
	return (print_length);
}

int	ft_iss(va_list args, int print_length)
{
	char	*str;

	str = va_arg(args, char *);
	print_length = ft_putandcountstr(str, print_length);
	if (!str)
	{
		write (1, "(null)", 6);
		print_length = 6;
	}
	return (print_length);
}
