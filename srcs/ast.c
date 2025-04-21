/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:12:48 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/21 17:34:07 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_ast	*find_pipes(t_lst	*token_list)
// {
// 	t_ast	*top_ast_node;
// 	t_ast	*head_ast_node;
// 	t_lst	*head_token;
// 	t_ast	*new_ast_node;
// 	t_token	*token;
	
// 	top_ast_node = malloc(1 * sizeof(t_ast));
// 	top_ast_node->node_list = NULL;
// 	head_ast_node = top_ast_node;
// 	head_token = token_list;
// 	while (head_token != NULL)
// 	{
// 		token = head_token->content;
// 		if (token->primary_type == PIPE)
// 		{
// 			ft_printf("Found first PIPE\n");
// 			head_ast_node->token = token;
// 			display_token(head_ast_node->token);
// 			head_token = head_token->next;
// 			break ;
// 		}	
// 		head_token = head_token->next;
// 	}
// 	while (head_token != NULL)
// 	{
// 		token = head_token->content;
// 		if (token->primary_type == PIPE)
// 		{
// 			ft_printf("Found more PIPEs\n");
// 			new_ast_node = malloc(1 * sizeof(t_ast));
// 			new_ast_node->token = token;
// 			new_ast_node->node_list = NULL;
// 			ft_lstadd_back(&head_ast_node->node_list, ft_lstnew(new_ast_node));
// 			display_token(new_ast_node->token);
// 			head_ast_node = new_ast_node;
// 		}
// 		head_token = head_token->next;
// 	}
// 	return (top_ast_node);
// }

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

// maybe might need more stoppers? not sure about it yet.
t_lst	*find_primary_token_right(t_lst *current_token_lst, enum primary_token_type token_type, int	size)
{
	t_lst	*head;
	t_token	*token;
	t_token	*current_token;
	int		index;

	if (current_token_lst == NULL)
		return (NULL);
	current_token = current_token_lst->content;
	if (current_token->primary_type == token_type)
		return (current_token_lst);
	index = 0;
	head = current_token_lst->next;
	while (head != NULL && index < size)
	{
		token = head->content;
		if (token->primary_type == token_type)
		{
			return (head);
		}
		else if (token->primary_type == current_token->primary_type)
		{
			return (NULL);
		}
		head = head->next;
		index++;
	}
	return (NULL);
}

t_lst	*find_primary_token_left(t_lst	**token_list, t_lst *current_token_lst, enum primary_token_type token_type, int size)
{
	t_lst	*previous_token_lst;
	t_token	*token;
	t_token	*current_token;
	int		index;

	if (current_token_lst == NULL)
		return (NULL);
	current_token = current_token_lst->content;
	if (current_token->primary_type == token_type)
		return (current_token_lst);
	index = 0;
	previous_token_lst = ft_lstgetprevious(token_list, current_token_lst);
	while (previous_token_lst != NULL && index < size)
	{
		token = previous_token_lst->content;
		if (token->primary_type == token_type)
		{
			return (previous_token_lst);
		}
		else if (token->primary_type == current_token->primary_type)
		{
			return (NULL);
		}
		previous_token_lst = ft_lstgetprevious(token_list, previous_token_lst);
		index++;
	}
	return (NULL);
}

t_lst	*find_secondary_token_right(t_lst *current_token_lst, enum secondary_token_type token_type, int size)
{
	t_lst	*head;
	t_token	*token;
	t_token	*current_token;
	int		index;

	if (current_token_lst == NULL)
		return (NULL);
	current_token = current_token_lst->content;
	if (current_token->secondary_type == token_type)
		return (current_token_lst);
	printf("b\n");
	index = 0;
	head = current_token_lst->next;
	while (head != NULL && index < size)
	{
		token = head->content;
		if (token->secondary_type == token_type)
		{
			return (head);
		}
		else if (token->secondary_type == current_token->secondary_type)
		{
			return (NULL);
		}
		head = head->next;
		index++;
	}
	printf("c\n");
	return (NULL);
}

t_lst	*find_secondary_token_left(t_lst	**token_list, t_lst *current_token_lst, enum secondary_token_type token_type, int size)
{
	t_lst	*previous_token_lst;
	t_token	*token;
	t_token	*current_token;
	int		index;

	if (current_token_lst == NULL)
		return (NULL);
	current_token = current_token_lst->content;
	if (current_token->secondary_type == token_type)
		return (current_token_lst);
	index = 0;
	previous_token_lst = ft_lstgetprevious(token_list, current_token_lst);
	while (previous_token_lst != NULL && index < size)
	{
		token = previous_token_lst->content;
		if (token->secondary_type == token_type)
		{
			return (previous_token_lst);
		}
		else if (token->secondary_type == current_token->secondary_type)
			return (NULL);
		previous_token_lst = ft_lstgetprevious(token_list, previous_token_lst);
		index++;
	}
	return (NULL);
}

void	display_ast_tree(t_ast *ast_node)
{
	t_lst	*head;

	ft_printf("--AST NODE TOKEN--\n");
	if (ast_node == NULL || ast_node->token == NULL)
	{
		printf("NULL\n\n");
		return ;
	}
	display_token(ast_node->token);
	printf("--AST NODE LIST--\n");
	if (ast_node->node_list == NULL)
		ft_printf("AST_NODE does not have NODE_LIST\n");
	head = ast_node->node_list;
	while (head != NULL)
	{
		ft_printf("iterating over list\n");
		if (head->content != NULL)
			display_ast_tree(head->content);
		head = head->next;
	}
}
