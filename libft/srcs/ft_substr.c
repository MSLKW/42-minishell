/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:53:56 by yilim             #+#    #+#             */
/*   Updated: 2024/03/05 17:53:56 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	s_len;
	size_t	res_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	s_len -= start;
	res_len = (s_len * (s_len < len)) + (len * (s_len >= len)) + 1;
	res = (char *)malloc(res_len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s + start, res_len);
	return (res);
}
