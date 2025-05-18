/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:48:08 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/16 23:53:38 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lststrdisplay(t_lst *list)
{
	t_lst	*head;

	ft_printf("---lst start---\n");
	head = list;
	while (head != NULL)
	{
		if (head->content != NULL)
			ft_printf("%s\n", head->content);
		else if (head->content == NULL)
			ft_printf("CONTENT IS NULL\n");
		head = head->next;
	}
	ft_printf("---lst end---\n");
}

void	debug_token_list(t_lst *token_list)
{
	t_lst	*head;

	ft_printf("-----TOKEN LIST-----\n");
	head = token_list;
	while (head != NULL)
	{
		display_token(head->content);
		head = head->next;
	}
}

void	display_token(t_token *token)
{
	if (token == NULL)
		printf("Token | content -> NULL\n");
	else
	{
		printf("Token | content -> \"%s\" | handler -> ", token->content);
		display_token_handler(token->handler);
		printf(" | primary_type -> ");
		display_primary_token_type(token->primary_type);
		printf(" | secondary_type -> ");
		display_secondary_token_type(token->secondary_type);
		printf("\n");
	}
}

void	display_token_handler(enum token_handler handler)
{
	if (handler == NONE)
		printf("NONE");
	else if (handler == DQUOTE)
		printf("DQUOTE");
	else if (handler == SQUOTE)
		printf("SQUOTE");
}

void	display_primary_token_type(enum primary_token_type type)
{
	if (type == ERROR)
		printf("ERROR");
	else if (type == WHITESPACE)
		printf("WHITESPACE");
	else if (type == ALPHANUMERIC)
		printf("ALPHANUMERIC");
	else if (type == ASCII)
		printf("ASCII");
	else if (type == SET_VALUE)
		printf("SET_VALUE");
	else if (type == PIPE)
		printf("PIPE");
	else if (type == REDIRECTION)
		printf("REDIRECTION");
	else if (type == VARIABLE)
		printf("VARIABLE");
}

void	display_secondary_token_type(enum secondary_token_type type)
{
	if (type == NOTHING)
		printf("NOTHING");
	else if (type == COMMAND)
		printf("COMMAND");
	else if (type == OPTION)
		printf("OPTION");
	else if (type == ARGUMENT)
		printf("ARGUMENT");
	else if (type == REDIRECTION_INPUT)
		printf("REDIRECTION_INPUT");
	else if (type == REDIRECTION_OUTPUT)
		printf("REDIRECTION_OUTPUT");
	else if (type == REDIRECTION_APPEND)
		printf("REDIRECTION_APPEND");
	else if (type == REDIRECTION_DELIMITER)
		printf("REDIRECTION_DELIMITER");
}

void	display_ast_tree(t_ast *ast_node)
{
	t_lst	*head;

	if (ast_node == NULL || ast_node->token == NULL)
	{
		printf("NULL\n\n");
		return ;
	}
	display_token(ast_node->token);
	printf("--AST NODE LIST (%s)--\n", ast_node->token->content);
	if (ast_node->node_list == NULL)
		ft_printf("AST_NODE does not have NODE_LIST\n");
	head = ast_node->node_list;
	while (head != NULL)
	{
		t_ast	*ast_list_node = head->content;
		display_token(ast_list_node->token);
		head = head->next;
	}
	printf("\n");
	head = ast_node->node_list;
	while (head != NULL)
	{
		t_ast	*ast_list_node_re = head->content;
		if (ast_list_node_re != NULL && ast_list_node_re->token->secondary_type != ARGUMENT)
			display_ast_tree(ast_list_node_re);
		head = head->next;
	}
}