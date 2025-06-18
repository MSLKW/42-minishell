/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 17:17:03 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 17:26:00 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_exit_code(t_data *data)
{
	if (g_sigint_received)
	{
		data->last_exit_code = 130;
		g_sigint_received = 0;
	}
}

void	history_helper(char	*line, t_data *data)
{
	add_history(line);
	store_history(data, line);
}
