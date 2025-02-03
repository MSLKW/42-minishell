/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:43:14 by yilim             #+#    #+#             */
/*   Updated: 2024/05/07 16:43:14 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_hex(va_list args, char c)
{
	unsigned int	n;
	char			*hex;
	int				len;

	n = va_arg(args, unsigned int);
	if (c == 'x')
		hex = ft_itoa_base(n, "0123456789abcdef");
	else
		hex = ft_itoa_base(n, "0123456789ABCDEF");
	len = ft_putstr(hex);
	free(hex);
	return (len);
}
