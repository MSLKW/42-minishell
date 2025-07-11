/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:58:47 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 17:30:19 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sigint_received = 0;

void	ctrlc_handler(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(1, "^C\n", 3);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrld_handler(t_data *data)
{
	write(1, "exit\n", 5);
	free_exit(data->last_exit_code, data);
}
