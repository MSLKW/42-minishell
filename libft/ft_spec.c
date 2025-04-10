/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 19:24:54 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/10 23:56:03 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	fspec_s(va_list ap)
{
	char	*str;

	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, FILE_DESCRIPTOR);
	return (ft_strlen(str));
}

int	fspec_p(va_list ap)
{
	int				char_count;
	unsigned long	ptr_address;

	char_count = 2;
	ptr_address = (unsigned long)va_arg(ap, void *);
	ft_putstr_fd("0x", FILE_DESCRIPTOR);
	ft_put_hex(ptr_address, 'x', &char_count);
	return (char_count);
}

int	fspec_d(va_list ap)
{
	int		val;

	val = va_arg(ap, int);
	ft_putnbr_fd(val, FILE_DESCRIPTOR);
	return (count_digits(val));
}

int	fspec_u(va_list ap)
{
	int	char_count;

	char_count = 0;
	ft_put_u_nbr_fd(va_arg(ap, unsigned int), FILE_DESCRIPTOR, &char_count);
	return (char_count);
}

int	fspec_x(va_list ap, const char format)
{
	int	char_count;

	char_count = 0;
	ft_put_hex(va_arg(ap, unsigned int), format, &char_count);
	return (char_count);
}
