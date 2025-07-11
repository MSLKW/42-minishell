/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_seq.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 17:48:43 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 15:14:44 by maxliew          ###   ########.fr       */
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
