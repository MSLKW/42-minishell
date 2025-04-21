/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:18:44 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 17:43:53 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hay_i;
	int		ndle_size;

	hay_i = 0;
	ndle_size = ft_strlen(needle);
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (hay_i < len && haystack[hay_i] != '\0')
	{
		if (len - hay_i >= (size_t)ndle_size
			&& ft_strncmp(haystack + hay_i, needle, ndle_size) == 0)
			return ((char *)haystack + hay_i);
		hay_i++;
	}
	return (NULL);
}
