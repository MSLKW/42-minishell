/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 02:47:52 by yilim             #+#    #+#             */
/*   Updated: 2024/03/04 02:47:52 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = 0;
	while (*(src + i++))
		*(dest + i - 1) = *(src + i - 1);
	*(dest + i - 1) = '\0';
	return (dest);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dest;

	len = ft_strlen(s);
	dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ft_strcpy(dest, (char *)s);
	return (dest);
}
