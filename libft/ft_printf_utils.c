/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:55:42 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/10 23:58:12 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define ASCII_GAP 33

void	ft_put_hex(unsigned long num, const char format, int *char_count)
{
	if (num >= 16)
	{
		ft_put_hex(num / 16, format, char_count);
		ft_put_hex(num % 16, format, char_count);
	}
	else
	{
		if (num < 10)
			ft_putchar_fd(num + '0', FILE_DESCRIPTOR);
		else
			ft_putchar_fd(num + format - ASCII_GAP, FILE_DESCRIPTOR);
		(*char_count)++;
	}
}

void	ft_put_u_nbr_fd(unsigned int n, int fd, int *char_count)
{
	if (n >= 10)
	{
		ft_put_u_nbr_fd(n / 10, fd, char_count);
		n = n % 10;
	}
	if (n < 10)
	{
		ft_putchar_fd(n + '0', fd);
		(*char_count)++;
	}
}

int	num_len(int num)
{
	char	*str;
	int		length;

	str = NULL;
	str = ft_itoa(num);
	if (str == NULL)
		return (-1);
	length = ft_strlen(str);
	free(str);
	return (length);
}
