/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:12:48 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/12 22:42:10 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*find_pipes(t_lst	*token_list)
{
	t_ast	*top_ast_node;
	t_ast	*head_ast_node;
	t_lst	*head_token;
	t_ast	*new_ast_node;
	t_token	*token;
	
	top_ast_node = malloc(1 * sizeof(t_ast));
	top_ast_node->node_list = NULL;
	head_ast_node = top_ast_node;
	head_token = token_list;
	while (head_token != NULL)
	{
		token = head_token->content;
		if (token->type == PIPE)
		{
			ft_printf("Found first PIPE\n");
			head_ast_node->token = token;
			display_token(head_ast_node->token);
			head_token = head_token->next;
			break ;
		}	
		head_token = head_token->next;
	}
	while (head_token != NULL)
	{
		token = head_token->content;
		if (token->type == PIPE)
		{
			ft_printf("Found more PIPEs\n");
			new_ast_node = malloc(1 * sizeof(t_ast));
			new_ast_node->token = token;
			new_ast_node->node_list = NULL;
			ft_lstadd_back(&head_ast_node->node_list, ft_lstnew(new_ast_node));
			display_token(new_ast_node->token);
			head_ast_node = new_ast_node;
		}
		head_token = head_token->next;
	}
	return (top_ast_node);
}

void	display_ast_tree(t_ast *ast_node)
{
	t_lst	*head;

	ft_printf("AST NODE\n");
	display_token(ast_node->token);
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
