/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:10:05 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/19 18:07:50 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	no_expand_heredoc(t_lst *token_list, t_lst *curr_token_lst, int size)
{
	t_lst	*previous_token_lst;
	t_token	*token;
	int		index;

	index = 0;
	previous_token_lst = curr_token_lst;
	while (previous_token_lst != NULL && index < size)
	{
		token = previous_token_lst->content;
		if (ft_strnstr(token->content, "<<", 3))
		{
			return (FALSE);
		}
		previous_token_lst = ft_lstgetprevious(&token_list, previous_token_lst);
		index++;
	}
	return (TRUE);
}

t_lst	*expand_variable_token_list(t_lst *token_list, t_data *data)
{
	t_lst	*head;
	t_token	*token;
	t_bool	status;
	char	*content_ptr;

	if (token_list == NULL)
		return (NULL);
	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		if ((token->handler == DQUOTE || token->handler == NONE) && \
no_expand_heredoc(token_list, head, 3))
		{
			content_ptr = token->content;
			token->content = variable_expansion(content_ptr, data, &status);
			if (status == TRUE && token->flags != NULL \
&& ft_strlen(token->content) > 0)
				token_add_flag(token->flags, WORD);
		}
		head = head->next;
	}
	return (token_list);
}
