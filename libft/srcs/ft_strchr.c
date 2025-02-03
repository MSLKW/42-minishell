/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 20:12:19 by yilim             #+#    #+#             */
/*   Updated: 2024/03/03 20:12:19 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (*(s + ++i))
		if (*(s + i) == (unsigned char)c)
			return ((char *)s + i);
	if ((unsigned char)c == 0)
		return ((char *)s + i);
	return (NULL);
}
