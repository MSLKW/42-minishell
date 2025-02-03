/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:21:02 by yilim             #+#    #+#             */
/*   Updated: 2024/03/05 22:21:02 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_size(char *str, char c);
static void		ft_put_split(char **res, char *str, char c);
static void		ft_word(char *dest, char *src, char c);

char	**ft_split(char const *s, char c)
{
	size_t	res_size;
	char	**res;

	if (!s)
		return (NULL);
	res_size = ft_size((char *)s, c);
	res = (char **)malloc(sizeof(char *) * (res_size + 1));
	if (!res)
		return (NULL);
	res[res_size] = 0;
	ft_put_split(res, (char *)s, c);
	return (res);
}

static size_t	ft_size(char *str, char c)
{
	int		i;
	size_t	size;

	i = -1;
	size = 0;
	while (str[++i])
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			size++;
	return (size);
}

static void	ft_put_split(char **res, char *str, char c)
{
	int	i;
	int	j;
	int	w;

	i = 0;
	w = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == '\0')
			i++;
		else
		{
			j = 0;
			while (!(str[i + j] == c || str[i + j] == '\0'))
				j++;
			res[w] = (char *)malloc(j + 1);
			if (!res[w])
				return ;
			ft_word(res[w], str + i, c);
			i += j;
			w++;
		}
	}
}

static void	ft_word(char *dest, char *src, char c)
{
	int	i;

	i = -1;
	while (!(src[++i] == c || src[i] == '\0'))
		dest[i] = src[i];
	dest[i] = '\0';
}
