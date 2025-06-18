/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 00:02:33 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 00:02:39 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_seqs(t_lst **cmd_seqs)
{
	ft_lstclear(cmd_seqs, free_cmd_seq);
	*cmd_seqs = NULL;
}

void	free_cmd_seq(void *content)
{
	t_cmd_seq	*cmd_seq;

	cmd_seq = (t_cmd_seq *)content;
	if (cmd_seq == NULL)
		return ;
	free_tokens(&cmd_seq->token_list);
	free(cmd_seq->assignment);
	free_str_arr(cmd_seq->argv);
	if (cmd_seq->io_list != NULL)
		ft_lstclear(&cmd_seq->io_list, free_io);
	free(cmd_seq);
}

void	free_io(void *content)
{
	t_io	*io;

	if (content == NULL)
		return ;
	io = (t_io *)content;
	if (io == NULL)
		return ;
	free(io->content);
	free(io);
}

void	free_env_var(void *content)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)content;
	if (env_var != NULL)
	{
		free(env_var->key);
		free(env_var->value);
		free(env_var);
	}
}
