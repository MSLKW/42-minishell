/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:18:34 by yilim             #+#    #+#             */
/*   Updated: 2024/03/07 19:18:34 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_numlen(int n);

char	*ft_itoa(int n)
{
	char	*res;
	size_t	num_len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	num_len = ft_numlen(n);
	res = (char *)malloc(num_len + 1);
	if (!res)
		return (NULL);
	res[num_len] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	while (n)
	{
		res[--num_len] = (char)(n % 10) + '0';
		n /= 10;
	}
	return (res);
}

static size_t	ft_numlen(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}
