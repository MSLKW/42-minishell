/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:57:51 by yilim             #+#    #+#             */
/*   Updated: 2024/05/06 16:08:50 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_itoa_base(unsigned long long n, char *base)
{
	char				*str;
	unsigned long long	nbr;
	int					len;
	int					base_len;

	base_len = ft_strlen(base);
	len = 1;
	nbr = n;
	while (nbr >= (unsigned long long)base_len)
	{
		nbr /= base_len;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	nbr = n;
	while (len--)
	{
		str[len] = base[nbr % base_len];
		nbr /= base_len;
	}
	return (str);
}
