/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:39:34 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/18 16:17:42 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_history(void)
{
	HIST_ENTRY **entries = history_list();
	int i;

	i = 0;
	if (!entries)
		return (1);

	while (entries[i])
	{
		printf("%d: %s\n", i + 1, entries[i]->line);
		i++;
	}
	return (0);
}

/*
void	ft_show_history(void)
{
	HIST_ENTRY **list = history_list(); // illegal function
	int	index;

	index = 0;
	if (list == NULL)
		return ;
	while (*list != NULL && index < 1000)
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

*/