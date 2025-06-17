/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:26:34 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 00:02:31 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free_str_arr(data->envp);
	ft_lstclear(&data->env_var_lst, free_env_var);
	free_str_arr(data->history);
	if (data->free_ptr_tokens != NULL)
		free_tokens(&data->free_ptr_tokens);
	if (data->free_ptr_cmd_seqs != NULL)
		free_cmd_seqs(&data->free_ptr_cmd_seqs);
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
	if (token == NULL)
		return ;
	free(token->content);
	free(token->flags);
	free(token);
}
