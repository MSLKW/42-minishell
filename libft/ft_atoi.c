/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:35:43 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/08 16:38:52 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	return (c == ' '
		|| c == '\n'
		|| c == '\t'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}

int	ft_atoi(const char *str)
{
	int	index;
	int	is_negative;
	int	number;

	index = 0;
	is_negative = 1;
	number = 0;
	while (ft_isspace(str[index]))
		index++;
	if (str[index] == '-' || str[index] == '+')
	{
		if (str[index] == '-')
			is_negative = -1;
		index++;
	}
	else if (ft_isdigit(str[index]) == 0)
		return (0);
	while (str[index] != '\0' && ft_isdigit(str[index]) == 1)
	{
		number = number * 10 + (str[index] - '0');
		index++;
	}
	return (number * is_negative);
}
