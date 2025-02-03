/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:00:23 by yilim             #+#    #+#             */
/*   Updated: 2024/05/06 15:00:23 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_ptr(va_list args)
{
	unsigned long	ptr;
	char			*hex;
	int				len;

	ptr = va_arg(args, unsigned long);
	hex = ft_itoa_base(ptr, "0123456789abcdef");
	len = ft_putstr("0x");
	len += ft_putstr(hex);
	free(hex);
	return (len);
}
