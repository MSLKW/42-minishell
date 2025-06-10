/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:48:08 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/11 00:51:21 by maxliew          ###   ########.fr       */
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
		printf(" | flags -> ");
		display_token_flags(token->flags);
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
	else if (handler == JOINT)
		printf("JOINT");
}

void	display_token_flag(enum token_flag flag)
{
	if (flag == DELIMITER)
		printf("DELIMITER");
	else if (flag == WHITESPACE)
		printf("WHITESPACE");
	else if (flag == OPERATOR)
		printf("OPERATOR");
	else if (flag == PIPE)
		printf("PIPE");
	else if (flag == REDIRECTION)
		printf("REDIRECTION");
	else if (flag == REDIRECTION_INPUT)
		printf("REDIRECTION_INPUT");
	else if (flag == REDIRECTION_OUTPUT)
		printf("REDIRECTION_OUTPUT");
	else if (flag == REDIRECTION_APPEND)
		printf("REDIRECTION_APPEND");
	else if (flag == REDIRECTION_DELIMITER)
		printf("REDIRECTION_DELIMITER");
	else if (flag == REDIRECTION_ARGUMENT)
		printf("REDIRECTION_ARGUMENT");
	else if (flag == WORD)
		printf("WORD");
	else if (flag == COMMAND)
		printf("COMMAND");
	else if (flag == ARGUMENT)
		printf("ARGUMENT");
	else if (flag == ASSIGNMENT)
		printf("ASSIGNMENT");
	else
		printf("%i", flag);
}

void	display_token_flags(enum token_flag *flags)
{
	int	i;

	if (flags == NULL)
	{
		printf("no_flag");
		return ;
	}
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flags[i] != NO_FLAG)
		{
			display_token_flag(flags[i]);
			printf(",");
		}
		i++;
	}
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
		if (ast_list_node_re != NULL && has_token_flag(ast_list_node_re->token->flags, ARGUMENT) == FALSE)
			display_ast_tree(ast_list_node_re);
		head = head->next;
	}
}

void	display_env_var(t_data *data)
{
	t_lst		*head;
	t_env_var	*env_var;
	
	printf("---env_var---\n");
	head = data->env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (env_var != NULL)
		{
			printf("display | env_var: %p | env_var key: %s | value: %s\n", env_var, env_var->key, env_var->value);
		}
		else
		{
			printf("env_var is null\n");
		}
		head = head->next;
	}
	printf("-------------\n");
}

void	display_str_arr(char **str_arr)
{
	int	i;

	if (str_arr == NULL)
		return ;
	i = 0;
	while (str_arr[i] != NULL)
	{
		printf("%s,", str_arr[i]);
		i++;
	}
}

void	display_io_list(t_lst *io_list)
{
	t_lst	*head;
	t_io	*io;

	head = io_list;
	while (head != NULL)
	{
		io = head->content;
		printf("io | io->content: %s | io->flag: ", io->content);
		display_token_flag(io->flag);
		printf("\n");
		head = head->next;
	}
}

void	display_cmd_seq(t_lst *cmd_seq_list)
{
	t_lst	*head;
	t_cmd_seq	*cmd_seq;

	printf("---Command Sequence---\n");
	head = cmd_seq_list;
	while (head != NULL)
	{
		cmd_seq = head->content;
		if (cmd_seq != NULL)
		{
			debug_token_list(cmd_seq->token_list);
			printf("cmd_seq->command: %s\n", cmd_seq->command);
			printf("cmd_seq->args: ");
			display_str_arr(cmd_seq->args);
			printf("\n");
			display_io_list(cmd_seq->io_list);
		}
		head = head->next;
	}
	printf("--------------------\n");
}