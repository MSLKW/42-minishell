/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:36:47 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/08 15:06:39 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*dest_uchar;
	unsigned char	*src_uchar;

	if (dest == NULL && src == NULL)
		return (dest);
	dest_uchar = (unsigned char *)dest;
	src_uchar = (unsigned char *)src;
	index = 0;
	while (index < n)
	{
		dest_uchar[index] = src_uchar[index];
		index++;
	}
	return (dest);
}
// while loop: maybe limit to end of src? (src != '\0')