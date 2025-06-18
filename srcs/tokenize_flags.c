/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:11:31 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 12:03:41 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_flags_cmd_arg_logic(t_token *token, int *cmd_line_flag)
{
	if (has_token_flag(token->flags, DELIMITER) == FALSE \
&& has_token_flag(token->flags, REDIRECTION_ARGUMENT) == FALSE)
	{
		if (has_token_flag(token->flags, WORD) \
&& has_token_flag(token->flags, ASSIGNMENT) == FALSE && *cmd_line_flag == 0)
		{
			token_add_flag(token->flags, COMMAND);
			*cmd_line_flag = 1;
		}
		else if ((has_token_flag(token->flags, WORD) \
|| has_token_flag(token->flags, ASSIGNMENT)) && *cmd_line_flag == 1)
			token_add_flag(token->flags, ARGUMENT);
		else if (has_token_flag(token->flags, PIPE) && *cmd_line_flag == 1)
			*cmd_line_flag = 0;
	}
}

/*
	Modifies the **token_list's token flags to 
	more suitable token types like COMMAND and ARGUMENT
*/
t_lst	*assign_flags_cmd_arg(t_lst **token_list)
{
	int		cmd_line_flag;
	t_lst	*head;
	t_token	*token;

	cmd_line_flag = 0;
	head = *token_list;
	while (head != NULL)
	{
		token = head->content;
		assign_flags_cmd_arg_logic(token, &cmd_line_flag);
		head = head->next;
	}
	return (*token_list);
}

void	assign_flags_redir_arg(t_lst *token_list)
{
	t_lst	*head;
	t_token	*token;
	int		redir_arg;

	head = token_list;
	redir_arg = 0;
	while (head != NULL)
	{
		token = head->content;
		if (has_token_flag(token->flags, REDIRECTION) && redir_arg == 0)
			redir_arg = 1;
		else if (has_token_flag(token->flags, WORD) && redir_arg == 1)
		{
			token_add_flag(token->flags, REDIRECTION_ARGUMENT);
			redir_arg = 0;
		}
		else
			redir_arg = 0;
		head = head->next;
	}
}
