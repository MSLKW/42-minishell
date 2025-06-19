/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:32:10 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/19 18:21:51 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ft_isalpha_str(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isalpha(str[index]) == FALSE)
			return (FALSE);
		index++;
	}
	return (TRUE);
}

int	count_null_terminated_arr(char **str_arr)
{
	int	count;

	count = 0;
	while (str_arr[count] != NULL)
		count++;
	return (count);
}

t_bool	ft_has_delimiter(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_is_delimiter(str[index]))
			return (TRUE);
		index++;
	}
	return (FALSE);
}

t_bool	ft_fully_delimiter(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_is_delimiter(str[index]) == FALSE)
			return (FALSE);
		index++;
	}
	return (TRUE);
}

t_bool	ft_is_delimiter(char c)
{
	return (c == ' ' || c == '\t');
}
