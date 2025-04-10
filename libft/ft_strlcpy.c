/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:35:13 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/08 13:31:01 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;

	index = -1;
	if (size == 0 || dest == NULL || src == NULL)
		return (ft_strlen(src));
	while (++index < size - 1 && src[index] != '\0')
	{
		dest[index] = src[index];
	}
	dest[index] = '\0';
	return (ft_strlen(src));
}
