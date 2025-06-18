/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_seqs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:14:46 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 15:16:34 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_cmd_seqs_mid_logic(t_token *token, \
t_lst **cmd_seq_token_list, t_lst **cmd_seq_list)
{
	t_cmd_seq	*cmd_seq;

	if (has_token_flag(token->flags, PIPE))
	{
		cmd_seq = init_cmd_seq(*cmd_seq_token_list);
		if (cmd_seq == NULL)
		{
			printf("Syntax error\n");
			return (1);
		}
		ft_lstadd_back(cmd_seq_list, ft_lstnew(cmd_seq));
		*cmd_seq_token_list = NULL;
	}
	else
		ft_lstadd_back(cmd_seq_token_list, \
ft_lstnew(init_token(token->content, token->handler, token->flags)));
	return (0);
}

static int	init_cmd_seqs_end_logic(t_lst **cmd_seq_token_list, \
t_lst **cmd_seq_list)
{
	t_cmd_seq	*cmd_seq;

	if (*cmd_seq_token_list != NULL)
	{
		cmd_seq = init_cmd_seq(*cmd_seq_token_list);
		if (cmd_seq == NULL)
		{
			printf("Syntax error\n");
			return (1);
		}
		ft_lstadd_back(cmd_seq_list, ft_lstnew(cmd_seq));
		*cmd_seq_token_list = NULL;
	}
	else if (*cmd_seq_token_list == NULL && *cmd_seq_list != NULL)
	{
		printf("Syntax error\n");
		if (*cmd_seq_list != NULL)
			ft_lstclear(cmd_seq_list, free_cmd_seq);
		return (1);
	}
	return (0);
}

t_lst	*init_cmd_seqs(t_lst *token_list)
{
	t_lst		*cmd_seq_list;
	t_lst		*head;
	t_token		*token;
	t_lst		*cmd_seq_token_list;

	cmd_seq_list = NULL;
	cmd_seq_token_list = NULL;
	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		if (init_cmd_seqs_mid_logic(token, \
&cmd_seq_token_list, &cmd_seq_list) == 1)
			return (NULL);
		head = head->next;
	}
	if (init_cmd_seqs_end_logic(&cmd_seq_token_list, &cmd_seq_list) == 1)
		return (NULL);
	return (cmd_seq_list);
}
