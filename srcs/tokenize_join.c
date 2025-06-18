/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_join.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:08:44 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 11:57:33 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_joint_content(char *joint_content, char *content)
{
	char	*free_ptr;

	if (joint_content != NULL && content == NULL)
		return (joint_content);
	else if (joint_content == NULL && content == NULL)
		return (NULL);
	else if (joint_content == NULL && content != NULL)
	{
		joint_content = ft_strdup(content);
	}
	else if (joint_content != NULL && content != NULL)
	{
		free_ptr = joint_content;
		joint_content = ft_strjoin(joint_content, content);
		free(free_ptr);
	}
	return (joint_content);
}

static t_token	*capture_new_token(char **joint_content, \
t_lst **new_token_list, t_flag *flags)
{
	t_token	*new_token;

	if (joint_content == NULL || *joint_content == NULL)
		return (NULL);
	new_token = init_token(*joint_content, NONE, flags);
	if (new_token == NULL)
		return (NULL);
	free(*joint_content);
	*joint_content = NULL;
	ft_lstadd_back(new_token_list, ft_lstnew(new_token));
	token_rm_flags(flags);
	return (new_token);
}

static void	join_token_logic(t_token *token, char **joint_content, \
t_flag *joint_flags, t_lst *new_token_list)
{
	if (has_token_flag(token->flags, OPERATOR) == TRUE)
	{
		capture_new_token(joint_content, &new_token_list, joint_flags);
		ft_lstadd_back(&new_token_list, \
ft_lstnew(init_token(token->content, token->handler, token->flags)));
	}
	else if (has_token_flag(token->flags, DELIMITER) == FALSE)
	{
		*joint_content = add_joint_content(*joint_content, token->content);
		if (!(has_token_flag(joint_flags, WORD) \
&& has_token_flag(token->flags, ASSIGNMENT)))
			token_add_flags(joint_flags, token->flags);
	}
	else if (has_token_flag(token->flags, DELIMITER) == TRUE)
		capture_new_token(joint_content, &new_token_list, joint_flags);
}

t_lst	*join_token_list(t_lst **token_list)
{
	t_lst	*head;
	t_lst	*new_token_list;
	t_token	*token;
	char	*joint_content;
	t_flag	*joint_flags;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	new_token_list = NULL;
	head = *token_list;
	joint_content = NULL;
	joint_flags = init_empty_token_flags();
	if (joint_flags == NULL)
		return (NULL);
	while (head != NULL)
	{
		token = head->content;
		join_token_logic(token, &joint_content, joint_flags, new_token_list);
		head = head->next;
	}
	if (joint_content != NULL)
		capture_new_token(&joint_content, &new_token_list, joint_flags);
	free(joint_flags);
	return (new_token_list);
}
