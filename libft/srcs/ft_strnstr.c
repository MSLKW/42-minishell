/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 01:21:56 by yilim             #+#    #+#             */
/*   Updated: 2024/03/04 01:21:56 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*small || (!(char *)big && !len))
		return ((char *)big);
	i = 0;
	while (*(big + i) && i < len)
	{
		j = 0;
		if (*(big + i) == *small)
		{
			while (*(big + i + j) == *(small + j) && *(small + j))
				j++;
			if (i + j > len)
				return (NULL);
			if (!*(small + j))
				return ((char *)big + i);
		}
		i++;
	}
	return (NULL);
}
