/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:32:10 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/13 11:06:35 by maxliew          ###   ########.fr       */
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

t_bool	ft_isalnum_str(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isalnum(str[index]) == FALSE)
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

t_bool	ft_has_whitespace(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == ' ')
			return (TRUE);
		index++;
	}
	return (FALSE);
}
