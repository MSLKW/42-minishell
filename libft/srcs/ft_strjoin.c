/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:19:29 by yilim             #+#    #+#             */
/*   Updated: 2024/03/05 18:19:29 by yilim            ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	s1_len;
	size_t	s2_len;
	size_t	res_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res_len = s1_len + s2_len + 1;
	res = (char *)malloc(res_len);
	if (!res)
		return (NULL);
	ft_strcpy(res, (char *)s1);
	ft_strcpy(res + s1_len, (char *)s2);
	return (res);
}
