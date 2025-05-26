/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:07:10 by zernest           #+#    #+#             */
/*   Updated: 2025/05/26 14:26:25 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_history(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->history_size)
		printf("%d: %s\n", i + 1, data->history[i]);
	return (0);
}

void	store_history(t_data *data, const char *line)
{
	char	**new_history;
	int		i;

	i = -1;
	new_history = malloc(sizeof(char *) * (data->history_size + 2));
	if (!new_history)
		return ;
	while (++i < data->history_size)
		new_history[i] = data->history[i];
	new_history[i] = ft_strdup(line);
	new_history[i + 1] = NULL;
	free(data->history);
	data->history = new_history;
	data->history_size++;
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