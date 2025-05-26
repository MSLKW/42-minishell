/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:26:34 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/26 16:42:28 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_envp(char **envp)
{
	int	i;

	if (envp == NULL)
		return ;
	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

void	free_str_arr(char **str_arr)
{
	int	i;

	if (str_arr == NULL)
		return ;
	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

void	free_data(t_data *data)
{
	free_envp(data->envp);
	ft_lstclear(&data->env_var_lst, free_env_var);
	free_str_arr(data->history);
	if (data->free_ptr_tokens != NULL)
		free_tokens(&data->free_ptr_tokens);
	if (data->free_ptr_ast != NULL)
		free_ast(&data->free_ptr_ast);
	free(data);
}

void	free_tokens(t_lst **tokens_lst)
{
	ft_lstclear(tokens_lst, free_token);
	*tokens_lst = NULL;
}

void	free_token(void *content)
{
	t_token	*token;

	token = (t_token *)content;
	free(token->content);
	free(token);
}
void	free_ast(t_ast **ast)
{
	if (ast == NULL || *ast == NULL)
		return ;
	free_ast_node(*ast);
	*ast = NULL;
}

void	free_ast_node(void	*content)
{
	t_ast	*ast_node;
	
	ast_node = (t_ast *)content;
	if (ast_node == NULL)
		return ;
	if (ast_node->node_list != NULL)
		ft_lstclear(&ast_node->node_list, free_ast_node);
	free(ast_node);
}