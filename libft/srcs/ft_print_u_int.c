/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_u_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:28:09 by yilim             #+#    #+#             */
/*   Updated: 2024/05/07 16:28:09 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_u_int(va_list args)
{
	unsigned int	n;
	char			*ui;
	int				len;

	n = va_arg(args, unsigned int);
	ui = ft_itoa_base(n, "0123456789");
	len = ft_putstr(ui);
	free(ui);
	return (len);
}
