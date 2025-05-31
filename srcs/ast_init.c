/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:57:03 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/31 22:43:16 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*init_ast(t_lst	**token_list)
{
	t_lst	*head;
	t_lst	*token_lst;
	t_ast	*node;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	head = *token_list;
	token_lst = find_token_right(head, PIPE, ft_lstsize(*token_list));
	if (token_lst != NULL)
	{
		node = init_pipe(token_list, token_lst);
		if (node == NULL)
			return (NULL);
		return (node);
	}
	token_lst = find_token_right(head, REDIRECTION, ft_lstsize(*token_list));
	// DEBUGGING 
	if (token_lst && token_lst->content)
	{
		t_token *tok = (t_token *)token_lst->content;
		printf("FOUND COMMAND: %s\n", tok->content);
	}
	// DEBUG ^
	if (token_lst != NULL)
	{
		node = init_redirection(token_list, token_lst);
		if (node == NULL)
			return (NULL);
		return (node);
	}
	token_lst = find_token_right(head, COMMAND, ft_lstsize(*token_list));
	if (token_lst != NULL)
	{
		node = init_command(token_lst);
		if (node == NULL)
			return (NULL);
		return (node);
	}
	token_lst = find_token_right(head, ASSIGNMENT, ft_lstsize(*token_list));
	if (token_lst != NULL)
	{
		node = init_setvalue(token_lst);
		if (node == NULL)
			return (NULL);
		return (node);
	}
	return (NULL);
}

t_ast	*init_pipe(t_lst **token_list, t_lst *pipe_token)
{
	t_ast	*result;
	t_lst	*redirection_token;
	t_lst	*command_token;
	t_ast	*redirection_ast;
	t_lst	*more_pipe_token;
	t_ast	*pipe_ast;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL)
		return (NULL);
	result->token = pipe_token->content;
	redirection_token = find_token_left(token_list, pipe_token, REDIRECTION, ft_lstsize(*token_list));
	if (redirection_token != NULL)
	{
		redirection_ast = init_redirection(token_list, redirection_token);
		ft_lstadd_back(&result->node_list, ft_lstnew(redirection_ast));
	}
	else if (redirection_token == NULL)
	{
		command_token = find_token_left(token_list, pipe_token, COMMAND, ft_lstsize(*token_list));
		if (command_token != NULL)
		{
			t_ast	*command_ast = init_command(command_token);
			ft_lstadd_back(&result->node_list, ft_lstnew(command_ast));
		}
	}
	more_pipe_token = find_token_right(pipe_token->next, PIPE, ft_lstsize(*token_list));
	if (more_pipe_token != NULL)
	{
		pipe_ast = init_pipe(token_list, more_pipe_token);
		ft_lstadd_back(&result->node_list, ft_lstnew(pipe_ast));
	}
	else if (more_pipe_token == NULL)
	{
		redirection_token = find_token_right(pipe_token, REDIRECTION, ft_lstsize(*token_list));
		if (redirection_token != NULL)
		{
			redirection_ast = init_redirection(token_list, redirection_token);
			ft_lstadd_back(&result->node_list, ft_lstnew(redirection_ast));
		}
		else if (redirection_token == NULL)
		{
			command_token = find_token_right(pipe_token, COMMAND, ft_lstsize(*token_list));
			if (command_token != NULL)
			{
				t_ast	*command_ast = init_command(command_token);
				ft_lstadd_back(&result->node_list, ft_lstnew(command_ast));
			}
		}
	}
	return (result);
}

// input < command
t_ast	*init_redirection(t_lst **token_list, t_lst *redirection_token)
{
	t_token	*token;

	token = redirection_token->content;
	if (has_token_flag(token->flags, REDIRECTION_INPUT) || has_token_flag(token->flags, REDIRECTION_DELIMITER))
	{
		return (init_input_redirection(token_list, redirection_token));
	}
	else if (has_token_flag(token->flags, REDIRECTION_OUTPUT) || has_token_flag(token->flags, REDIRECTION_APPEND))
	{
		return (init_output_redirection(token_list, redirection_token));
	}
	return (NULL);
}

t_ast	*init_input_redirection(t_lst **token_list, t_lst *redirection_token)
{
	t_ast	*result;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL || redirection_token == NULL || redirection_token->content == NULL )
		return (NULL);
	result->token = redirection_token->content;;
	t_lst *input_arg = find_token_left(token_list, redirection_token, WORD, 3); // ARGUMENT | 2
	if (input_arg == NULL)
		return (NULL);
	ft_lstadd_back(&result->node_list, ft_lstnew(init_argument(input_arg)));
	t_lst	*cmd_token_lst = find_token_right(redirection_token, COMMAND, 3); // 2
	if (cmd_token_lst == NULL)
		return (NULL);
	ft_lstadd_back(&result->node_list, ft_lstnew(init_command(cmd_token_lst)));
	return (result);
}

t_ast	*init_output_redirection(t_lst **token_list, t_lst *redirection_token)
{
	t_ast	*result;
	t_lst	*cmd_lst;
	t_lst	*pipe_lst;
	t_lst	*output_arg;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL)
		return (NULL);
	result->token = redirection_token->content;
	pipe_lst = find_token_left(token_list, redirection_token, PIPE, ft_lstsize(*token_list));
	if (pipe_lst != NULL)
		cmd_lst = find_token_right(pipe_lst, COMMAND, 3); // 2
	else if (pipe_lst == NULL)
		cmd_lst = find_token_left(token_list, redirection_token, COMMAND, ft_lstsize(*token_list));
	if (cmd_lst == NULL)
		return (NULL);
	output_arg = find_token_right(redirection_token, WORD, 3); // 2
	if (output_arg == NULL)
		return (NULL);
	ft_lstadd_back(&result->node_list, ft_lstnew(init_command(cmd_lst)));
	ft_lstadd_back(&result->node_list, ft_lstnew(init_argument(output_arg)));
	return (result);
}

t_ast	*init_command(t_lst	*command_token)
{
	t_ast	*result;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL)
		return (NULL);
	result->token = command_token->content;
	result->node_list = NULL;
	t_lst	*arg_token_lst = find_token_right(command_token, ARGUMENT, 3);
	while (arg_token_lst != NULL)
	{
		ft_lstadd_back(&result->node_list, ft_lstnew(init_argument(arg_token_lst)));
		arg_token_lst = find_token_right(arg_token_lst->next, ARGUMENT, 3);
	}
	return (result);
}

t_ast	*init_argument(t_lst *argument_token)
{
	t_ast	*result;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL)
		return (NULL);
	result->token = argument_token->content;
	result->node_list = NULL;
	return (result);
}
// static t_lst	*get_setvalue_arg(t_lst	*setvalue_token)
// {
// 	t_lst	*token_lst;

// 	token_lst = NULL;
// 	token_lst = find_token_right(setvalue_token, ASCII, 2);
// 	if (token_lst == NULL)
// 		token_lst = find_token_right(setvalue_token, ALPHANUMERIC, 2);
// 	setvalue_token = setvalue_token->next;
// 	if (token_lst == NULL)
// 		token_lst = find_token_right(setvalue_token, SET_VALUE, 2);
// 	return (token_lst);
// }

t_ast	*init_setvalue(t_lst *setvalue_token)
{
	t_ast	*result;
	// t_lst	*token_lst;
	// t_token	*token;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL)
		return (NULL);
	result->token = setvalue_token->content;
	result->node_list = NULL;
	// token_lst = setvalue_token->next;
	// if (token_lst == NULL)
	// 	return (result);
	// token = token_lst->next->content;
	// while (token->right_white_space == FALSE && )
	// if (result->token->right_white_space == FALSE)
	// {
	// 	token_lst = get_setvalue_arg(setvalue_token);
	// 	while (token_lst != NULL)
	// 	{
	// 		ft_lstadd_back(&result->node_list, ft_lstnew(init_argument(token_lst)));
	// 		token_lst = get_setvalue_arg(token_lst);
	// 	}
	// }
	return (result);
}
