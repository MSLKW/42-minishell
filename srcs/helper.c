/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 15:32:10 by maxliew           #+#    #+#             */
/*   Updated: 2025/03/08 15:37:18 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha_str(char *str)
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

int	ft_isalnum_str(char *str)
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