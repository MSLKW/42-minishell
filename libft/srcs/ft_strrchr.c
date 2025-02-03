/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:25:05 by yilim             #+#    #+#             */
/*   Updated: 2024/03/03 20:25:05 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if ((unsigned char)c == 0)
		return ((char *)(s + s_len));
	while (s_len > 0)
	{
		if (*(s + s_len - 1) == (unsigned char)c)
			return ((char *)(s + s_len - 1));
		s_len--;
	}
	return (NULL);
}
