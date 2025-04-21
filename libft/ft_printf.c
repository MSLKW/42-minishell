/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:17:18 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/10 23:56:00 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *text, ...)
{
	int		i;
	int		char_count;
	va_list	ap;

	i = 0;
	char_count = 0;
	va_start(ap, text);
	while (text[i] != '\0')
	{
		if (text[i] == '%')
		{
			i++;
			char_count += process_format_specifier(text[i], ap);
		}
		else
		{
			ft_putchar_fd(text[i], 1);
			char_count++;
		}
		i++;
	}
	va_end(ap);
	return (char_count);
}

int	process_format_specifier(char f_spec, va_list ap)
{
	int	char_count;

	char_count = 0;
	if (f_spec == 'c')
		char_count += fspec_c(ap);
	else if (f_spec == 's')
		char_count += fspec_s(ap);
	else if (f_spec == 'p')
		char_count += fspec_p(ap);
	else if (f_spec == 'd')
		char_count += fspec_d(ap);
	else if (f_spec == 'i')
		char_count += fspec_d(ap);
	else if (f_spec == 'u')
		char_count += fspec_u(ap);
	else if (f_spec == 'x')
		char_count += fspec_x(ap, f_spec);
	else if (f_spec == 'X')
		char_count += fspec_x(ap, f_spec);
	else if (f_spec == '%')
	{
		ft_putchar_fd('%', FILE_DESCRIPTOR);
		char_count = 1;
	}
	return (char_count);
}

int	fspec_c(va_list ap)
{
	ft_putchar_fd(va_arg(ap, int), FILE_DESCRIPTOR);
	return (1);
}
