/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:00:48 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 15:07:44 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int	index;
	int	rindex;

	if (s1 == NULL || set == NULL)
		return (NULL);
	index = 0;
	rindex = ft_strlen(s1) - NULL_SIZE;
	if (s1[index] == '\0')
		return (ft_substr("", 0, 0));
	if (set[index] == '\0')
		return (ft_substr(s1, 0, ft_strlen(s1)));
	while (s1[index] != '\0' && ft_strchr(set, s1[index]) != NULL)
		index++;
	while (rindex > index && ft_strchr(set, s1[rindex]) != NULL)
		rindex--;
	return (ft_substr(s1, index, (rindex - index + 1)));
}
