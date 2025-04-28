/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_search.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:12:48 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/28 15:58:33 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*find_primary_token_right(t_lst *current_token_lst, enum primary_token_type token_type, int	size)
{
	t_lst	*head;
	t_token	*token;
	t_token	*current_token;
	int		index;

	if (current_token_lst == NULL)
		return (NULL);
	current_token = current_token_lst->content;
	printf("size: %i\n", size);
	if (current_token->primary_type == token_type)
		return (current_token_lst);
	index = 0;
	head = current_token_lst->next;
	printf("c\n");
	while (head != NULL && index < size)
	{
		printf("d\n");
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
		printf("e\n");
	}
	printf("f\n");
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