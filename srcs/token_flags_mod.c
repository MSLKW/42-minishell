/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flags_mod.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:17:07 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 00:17:31 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Returns 0 on success
	Returns 1 on input error
	Returns 2 if no space in flag_arr
*/
int	token_add_flag(t_flag *flag_arr, t_flag flag)
{
	int	i;

	if (flag_arr == NULL || flag == NO_FLAG)
		return (1);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flag_arr[i] == NO_FLAG || flag_arr[i] == flag)
		{
			flag_arr[i] = flag;
			return (0);
		}
		i++;
	}
	return (2);
}

/*
	Returns 0 on success
	Returns 1 on input error
	Returns 2 if no space in flag_arr
*/
int	token_add_flags(t_flag *flag_arr, t_flag *new_flag_arr)
{
	int	i;

	if (flag_arr == NULL || new_flag_arr == NULL)
		return (1);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (has_token_flag(flag_arr, new_flag_arr[i]) == FALSE)
		{
			if (token_add_flag(flag_arr, new_flag_arr[i]) == 2)
				return (2);
		}
		i++;
	}
	return (0);
}

/*
	Returns 0 on success, Returns 1 on error
*/
int	token_rm_flag(t_flag *flag_arr, t_flag flag)
{
	int	i;
	int	success;

	if (flag_arr == NULL || flag == NO_FLAG)
		return (1);
	success = 1;
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flag_arr[i] == flag)
		{
			flag_arr[i] = NO_FLAG;
			success = 0;
		}
		i++;
	}
	return (success);
}

int	token_rm_flags(t_flag *flag_arr)
{
	int	i;

	if (flag_arr == NULL)
		return (1);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		flag_arr[i] = NO_FLAG;
		i++;
	}
	return (0);
}
