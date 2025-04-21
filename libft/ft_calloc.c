/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:35:41 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 14:35:48 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if ((size != 0 && count > UINT_MAX / size)
		|| (count != 0 && size > UINT_MAX / count))
		ptr = NULL;
	else
	{
		ptr = malloc(size * count);
		if (ptr == NULL)
			return (NULL);
		ft_bzero(ptr, size * count);
	}
	return (ptr);
}
