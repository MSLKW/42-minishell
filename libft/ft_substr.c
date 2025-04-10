/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 12:59:24 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 17:53:27 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*new_str;

	if (s == NULL)
		return (NULL);
	if (len > (size_t)ft_strlen(s))
		len = (size_t)ft_strlen(s);
	new_str = ft_calloc(len + NULL_SIZE, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	else if (start >= (unsigned int)ft_strlen(s))
		return (new_str);
	ft_strlcpy(new_str, (char *)s + start, len + NULL_SIZE);
	return (new_str);
}
