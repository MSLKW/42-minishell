/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_seq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:48:43 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 14:21:20 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_seq	*init_cmd_seq(t_lst	*token_list)
{
	t_cmd_seq	*cmd_seq;
	int			status;

	status = 0;
	if (token_list == NULL)
		return (NULL);
	cmd_seq = ft_calloc(1, sizeof(t_cmd_seq));
	if (cmd_seq == NULL || token_list == NULL)
		return (NULL);
	cmd_seq->token_list = token_list;
	cmd_seq->assignment = cmd_seq_get_assignment(token_list);
	cmd_seq->argv = cmd_seq_get_argv(token_list);
	cmd_seq->io_list = get_io_list(token_list, &status);
	if (status == 1)
	{
		free_cmd_seq(cmd_seq);
		return (NULL);
	}
	return (cmd_seq);
}

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

char	*cmd_seq_get_assignment(t_lst *token_list)
{
	t_lst	*head;
	t_token	*token;

	if (token_list == NULL)
		return (NULL);
	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		if (has_token_flag(token->flags, ASSIGNMENT))
			return (ft_strdup(token->content));
		head = head->next;
	}
	return (NULL);
}

char	**cmd_seq_get_argv(t_lst *tkn_list)
{
	char	**args_arr;
	int		size;
	int		i;
	t_lst	*head;
	t_token	*token;

	size = tkn_flg_num(tkn_list, ARGUMENT) + tkn_flg_num(tkn_list, COMMAND);
	if (tkn_list == NULL || size == -1)
		return (NULL);
	args_arr = ft_calloc(size + 1, sizeof(char *));
	head = tkn_list;
	i = 0;
	while (head != NULL && i < size)
	{
		token = head->content;
		if (has_token_flag(token->flags, COMMAND) || \
has_token_flag(token->flags, ARGUMENT))
		{
			args_arr[i] = ft_strdup(token->content);
			i++;
		}
		head = head->next;
	}
	args_arr[i] = NULL;
	return (args_arr);
}
