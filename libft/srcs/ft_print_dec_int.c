/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_dec_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:10:58 by yilim             #+#    #+#             */
/*   Updated: 2024/05/07 16:20:50 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_print_dec_int(va_list args)
{
	int		num;
	int		len;
	char	*dec;

	num = va_arg(args, int);
	dec = ft_itoa(num);
	len = ft_putstr(dec);
	free(dec);
	return (len);
}
