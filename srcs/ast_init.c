/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:57:03 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/28 15:58:14 by maxliew          ###   ########.fr       */
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
	printf("looking for pipe\n");
	token_lst = find_primary_token_right(head, PIPE, ft_lstsize(*token_list));
	printf("token_lst: %p\n", token_lst);
	if (token_lst != NULL)
	{
		node = init_pipe(token_list, token_lst);
		if (node == NULL)
			return (NULL);
		return (node);
	}
	printf("looking for redirection\n");
	token_lst = find_primary_token_right(head, REDIRECTION, ft_lstsize(*token_list));
	if (token_lst != NULL)
	{
		node = init_redirection(token_list, token_lst);
		if (node == NULL)
			return (NULL);
		return (node);
	}
	printf("looking for command\n");
	token_lst = find_secondary_token_right(head, COMMAND, ft_lstsize(*token_list));
	if (token_lst != NULL)
	{
		node = init_command(token_lst);
		if (node == NULL)
			return (NULL);
		return (node);
	}
	printf("nothing found\n");
	return (NULL);
}

t_ast	*init_pipe(t_lst **token_list, t_lst *pipe_token)
{
	t_ast	*result;
	t_lst	*redirection_token;
	t_lst	*command_token;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL)
		return (NULL);
	result->token = pipe_token->content;
	redirection_token = find_primary_token_left(token_list, pipe_token, REDIRECTION, ft_lstsize(*token_list));
	if (redirection_token != NULL)
	{
		t_ast	*redirection_ast = init_redirection(token_list, redirection_token);
		ft_lstadd_back(&result->node_list, ft_lstnew(redirection_ast));
	}
	else if (redirection_token == NULL)
	{
		command_token = find_secondary_token_left(token_list, pipe_token, COMMAND, ft_lstsize(*token_list));
		if (command_token != NULL)
		{
			t_ast	*command_ast = init_command(command_token);
			printf("add command to node_list\n");
			ft_lstadd_back(&result->node_list, ft_lstnew(command_ast));
		}
	}
	t_lst	*more_pipe_token = find_primary_token_right(pipe_token, PIPE, ft_lstsize(*token_list));
	if (more_pipe_token != NULL)
	{
		t_ast	*pipe_ast = init_pipe(token_list, more_pipe_token);
		ft_lstadd_back(&result->node_list, ft_lstnew(pipe_ast));
	}
	return (result);
}

t_ast	*init_redirection(t_lst **token_list, t_lst *redirection_token)
{
	t_ast	*result;

	result = ft_calloc(1, sizeof(t_ast));
	if (result == NULL)
		return (NULL);
	result->token = redirection_token->content;
	if (result == NULL)
		return (NULL);
	t_lst *input_arg = find_primary_token_left(token_list, redirection_token, REDIRECTION, 2);
	if (input_arg == NULL)
	{
		return (NULL);
	}
	t_lst	*cmd_token_lst = find_secondary_token_right(redirection_token, COMMAND, 2);
	if (cmd_token_lst == NULL)
		return (NULL);
	t_token	*input_arg_token = input_arg->content;
	if (input_arg_token->primary_type == ASCII || input_arg_token->primary_type == ALPHANUMERIC)
	{
		ft_lstadd_back(&result->node_list, ft_lstnew(init_argument(input_arg)));
	}
	ft_lstadd_back(&result->node_list, ft_lstnew(init_command(cmd_token_lst)));
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
	t_lst	*arg_token_lst = find_secondary_token_right(command_token, ARGUMENT, 2);
	while (arg_token_lst != NULL)
	{
		ft_lstadd_back(&result->node_list, ft_lstnew(init_argument(arg_token_lst)));
		arg_token_lst = find_secondary_token_right(arg_token_lst->next, ARGUMENT, 2);
	}
	return (result);
}

t_ast	*init_argument(t_lst *argument_token)
{
	t_ast *result;

	result = ft_calloc(1, sizeof(t_ast));
	result->token = argument_token->content;
	result->node_list = NULL;
	return (result);
}
