/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function_helper.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:57:58 by zernest           #+#    #+#             */
/*   Updated: 2025/06/19 19:59:35 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_norminette(t_cmd_seq *cmd_seq, t_data *data)
{
	apply_redirections(cmd_seq->io_list, data);
	execve_wrapper(cmd_seq, data);
}
