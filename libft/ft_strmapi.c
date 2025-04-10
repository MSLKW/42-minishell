/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:35:24 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/07 11:17:49 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	index;
	char			*new_str;

	if (s == NULL || f == NULL)
		return (NULL);
	new_str = ft_strdup(s);
	if (new_str == NULL)
		return (NULL);
	index = 0;
	while (new_str[index] != '\0')
	{
		new_str[index] = f(index, s[index]);
		index++;
	}
	return (new_str);
}
