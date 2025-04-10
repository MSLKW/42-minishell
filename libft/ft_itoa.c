/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:31:59 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 18:07:13 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = -n;
		count++;
	}
	while (n >= 10)
	{
		n /= 10;
		count++;
	}
	return (count + 1);
}

static	void	ft_addnb(int n, char *nb_str)
{
	char	str[1];

	if (n == -2147483648)
	{
		ft_strlcpy(nb_str, "-2147483648", 11 + NULL_SIZE);
		return ;
	}
	if (n < 0)
	{
		ft_strlcpy(nb_str, "-", 1 + NULL_SIZE);
		n = -n;
	}
	if (n >= 10)
	{
		ft_addnb(n / 10, nb_str);
		n = n % 10;
	}
	if (n < 10)
	{
		str[0] = n + '0';
		ft_strlcat(nb_str, str, ft_strlen(nb_str) + 1 + NULL_SIZE);
	}
}

char	*ft_itoa(int n)
{
	char	*nb_str;
	int		count;

	count = count_digits(n);
	nb_str = ft_calloc(count + NULL_SIZE, sizeof(char));
	if (nb_str == NULL)
		return (NULL);
	ft_addnb(n, nb_str);
	return (nb_str);
}
