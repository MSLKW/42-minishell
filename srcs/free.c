/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:26:34 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/17 16:57:00 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_str_arr(char **str_arr)
{
	int	i;

	if (str_arr == NULL)
		return ;
	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_data(t_data *data)
{
	free_envp(data->envp);
	ft_lstclear(&data->env_var_lst, free_env_var);
	free_str_arr(data->history);
	if (data->free_ptr_tokens != NULL)
		free_tokens(&data->free_ptr_tokens);
	if (data->free_ptr_cmd_seqs != NULL)
		free_cmd_seqs(&data->free_ptr_cmd_seqs);
	free(data);
}

void	free_tokens(t_lst **tokens_lst)
{
	ft_lstclear(tokens_lst, free_token);
	*tokens_lst = NULL;
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	if (token == NULL)
		return ;
	free(token->content);
	free(token->flags);
	free(token);
}

void	free_cmd_seqs(t_lst **cmd_seqs)
{
	if (cmd_seqs == NULL)
	{
		printf("free_cmd_seqs: got NULL pointer\n");
		return;
	}
	if (*cmd_seqs == NULL)
	{
		printf("free_cmd_seqs: list already NULL\n");
		return;
	}
	// Print debug info
	t_lst *tmp = *cmd_seqs;
	while (tmp)
	{
		printf("free_cmd_seqs: freeing cmd_seq at %p\n", tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(cmd_seqs, free_cmd_seq);
	*cmd_seqs = NULL;
}

void	free_cmd_seq(void *content)
{
	t_cmd_seq *cmd_seq;

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
	t_io *io;

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
