/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:39:34 by maxliew           #+#    #+#             */
/*   Updated: 2025/02/17 19:01:10 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_show_history(void)
{
	HIST_ENTRY **list = history_list(); // illegal function
	int	index;

	index = 0;
	while (*list != NULL)
	{
		printf(" %i %s\n", index, (*list)->line);
		index++;
		list++;
	}
}

void	ft_clear_history(void)
{
	rl_clear_history();
}