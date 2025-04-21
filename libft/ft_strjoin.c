/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:49:58 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 18:03:19 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*joined_str;
	size_t	joined_str_size;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined_str_size = ft_strlen(s1) + ft_strlen(s2) + NULL_SIZE;
	joined_str = ft_calloc(joined_str_size, sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	ft_strlcpy(joined_str, (char *)s1, ft_strlen(s1) + NULL_SIZE);
	ft_strlcat(joined_str, (char *)s2, joined_str_size);
	return (joined_str);
}
