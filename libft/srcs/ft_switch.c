/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_switch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:25:12 by yilim             #+#    #+#             */
/*   Updated: 2024/05/06 13:25:12 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_switch(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 'c')
		len += ft_print_char(args);
	else if (c == 's')
		len += ft_print_str(args);
	else if (c == 'p')
		len += ft_print_ptr(args);
	else if (c == 'd' || c == 'i')
		len += ft_print_dec_int(args);
	else if (c == 'u')
		len += ft_print_u_int(args);
	else if (c == 'x' || c == 'X')
		len += ft_print_hex(args, c);
	else if (c == '%')
		len += ft_putchar('%');
	else
		len += ft_putchar(c);
	return (len);
}
