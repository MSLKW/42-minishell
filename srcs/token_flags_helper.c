/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flags_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:18:26 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 00:19:09 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_token_flag(t_flag *flags, t_flag flag)
{
	int	i;

	if (flags == NULL)
		return (FALSE);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flags[i] == flag)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_token_flags_empty(t_flag *flags_arr)
{
	int	i;

	if (flags_arr == NULL)
		return (TRUE);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flags_arr[i] != NO_FLAG)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	count_token_with_flag(t_lst	*token_list, t_flag flag)
{
	int		count;
	t_lst	*head;
	t_token	*token;

	if (token_list == NULL)
		return (-1);
	count = 0;
	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		if (has_token_flag(token->flags, flag) == TRUE)
			count++;
		head = head->next;
	}
	return (count);
}

