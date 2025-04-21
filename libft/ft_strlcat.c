/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:11:27 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 15:36:41 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_length;
	size_t	src_length;
	size_t	src_index;

	if (dest == NULL && size == 0)
		return (0);
	dest_length = ft_strlen(dest);
	src_length = ft_strlen(src);
	if (size <= dest_length)
		return (src_length + size);
	src_index = 0;
	while (src[src_index] != '\0' && src_index < size - dest_length - 1)
	{
		dest[dest_length + src_index] = src[src_index];
		src_index++;
	}
	dest[dest_length + src_index] = '\0';
	return (dest_length + src_length);
}
