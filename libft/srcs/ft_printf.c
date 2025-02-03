/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:23:23 by yilim             #+#    #+#             */
/*   Updated: 2024/04/29 15:23:23 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	char	*s;

	va_start(args, str);
	len = 0;
	s = (char *)str;
	while (*s)
	{
		if (*s == '%')
			len += ft_switch(*(++s), args);
		else
			len += ft_putchar(*s);
		s++;
	}
	va_end(args);
	return (len);
}
