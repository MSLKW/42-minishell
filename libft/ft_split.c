/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:53:06 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/10 14:40:13 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	word_flag;

	count = 0;
	word_flag = 0;
	while (*s != '\0')
	{
		if (word_flag == 0 && *s != c)
			word_flag = 1;
		else if (word_flag == 1 && *s == c)
		{
			count++;
			word_flag = 0;
		}
		s++;
	}
	if (word_flag == 1)
		count++;
	return (count);
}

char	**ft_split(const char *s, char c)
{
	int		start;
	int		index;
	int		arr_index;
	char	**split_arr;

	if (s == NULL)
		return (NULL);
	split_arr = ft_calloc(count_words(s, c) + NULL_SIZE, sizeof(char *));
	if (split_arr == NULL)
		return (NULL);
	index = -1;
	start = -1;
	arr_index = 0;
	while (++index < ft_strlen(s) + NULL_SIZE)
	{
		if (start == -1 && s[index] != c)
			start = index;
		else if (start >= 0 && (s[index] == c || s[index] == '\0'))
		{
			split_arr[arr_index++] = ft_substr(s, start, index - start);
			start = -1;
		}
	}
	split_arr[arr_index] = NULL;
	return (split_arr);
}
// start acts as a word_flag and an index for substr