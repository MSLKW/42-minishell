/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:38:42 by yilim             #+#    #+#             */
/*   Updated: 2024/03/07 19:38:42 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = ft_strlen(s);
	res = (char *)malloc(i + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (*(s + i))
	{
		*(res + i) = f(i, *(s + i));
		i++;
	}
	*(res + i) = '\0';
	return (res);
}
