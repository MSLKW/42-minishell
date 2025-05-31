/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:12:48 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/31 22:34:58 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*find_token_right(t_lst *current_token_lst, t_flag token_flag, int size)
{
	t_lst	*head;
	t_token	*token;
	int		index;

	index = 0;
	head = current_token_lst;
	while (head != NULL && index < size)
	{
		token = head->content;
		if (has_token_flag(token->flags, token_flag))
		{
			return (head);
		}
		head = head->next;
		index++;
	}
	return (NULL);
}

t_lst	*find_token_left(t_lst	**token_list, t_lst *current_token_lst, t_flag token_flag, int size)
{
	t_lst	*previous_token_lst;
	t_token	*token;
	int		index;

	index = 0;
	previous_token_lst = current_token_lst;
	while (previous_token_lst != NULL && index < size)
	{
		token = previous_token_lst->content;
		if (has_token_flag(token->flags, token_flag))
		{
			return (previous_token_lst);
		}
		previous_token_lst = ft_lstgetprevious(token_list, previous_token_lst);
		index++;
	}
	return (NULL);
}
