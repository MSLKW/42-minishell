/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:36:50 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/08 15:06:45 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_uchar;
	unsigned char	*src_uchar;

	if (dst == NULL && src == NULL)
		return (dst);
	dst_uchar = (unsigned char *)dst;
	src_uchar = (unsigned char *)src;
	if (dst_uchar > src_uchar)
		while (len-- > 0)
			dst_uchar[len] = src_uchar[len];
	else
	{
		while (len-- > 0)
		{
			*dst_uchar = *src_uchar;
			dst_uchar++;
			src_uchar++;
		}
	}
	return (dst);
}
