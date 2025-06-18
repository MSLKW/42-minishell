/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:12:35 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 22:39:33 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_and_return(t_data *data)
{
	free_tokens(&data->free_ptr_tokens);
	free_cmd_seqs(&data->free_ptr_cmd_seqs);
}

int	execute_cmd_seqs(t_lst *cmd_seqs, t_data *data)
{
	t_cmd_seq	*cmd_seq;
	int			status;		

	if (cmd_seqs == NULL)
		return (1);
	cmd_seq = cmd_seqs->content;
	if (cmd_seq == NULL)
		return (1);
// 	printf("size %i, %i, %p\n", ft_lstsize(cmd_seqs), count_null_terminated_arr(cmd_seq->argv) 
// , cmd_seq->assignment);
	if (process_heredocs(cmd_seqs, data) != 0)
	{
		status = 1;
	}
	if (ft_lstsize(cmd_seqs) > 1)
		status = execute_pipeline(cmd_seqs, data);
	else if (ft_lstsize(cmd_seqs) == 1
		&& count_null_terminated_arr(cmd_seq->argv) == 0
		&& cmd_seq->assignment != NULL)
		status = execute_assignment(cmd_seq, data);
	else if (count_null_terminated_arr(cmd_seq->argv) >= 1)
		status = execute_command(cmd_seq, data);
	else
		status = -1;
	if (status != -1)
		cleanup_and_return(data);
	return (status);
}

int	execute_assignment(t_cmd_seq *cmd_seq, t_data *data)
{
	t_env_var	*env_var;

	env_var = split_assignment(cmd_seq->assignment);
	if (env_var == NULL || env_var->key == NULL)
		return (1);
	set_env_variable(data->env_var_lst, env_var, &data->envp);
	return (0);
}
