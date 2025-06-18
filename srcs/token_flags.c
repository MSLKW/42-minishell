/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:08:50 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 13:46:32 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_flag	*init_empty_token_flags(void)
{
	t_flag	*flag_arr;

	flag_arr = ft_calloc(TOKEN_FLAG_SIZE, sizeof(t_flag));
	if (flag_arr == NULL)
		return (NULL);
	return (flag_arr);
}

static t_flag	*add_operator_flags(t_flag *flag_arr, char *content, int size)
{
	token_add_flag(flag_arr, OPERATOR);
	if (ft_strchr(content, '|') && size == 1)
	{
		token_add_flag(flag_arr, PIPE);
		return (flag_arr);
	}
	token_add_flag(flag_arr, REDIRECTION);
	if (ft_strchr(content, '<') && size == 1)
		token_add_flag(flag_arr, REDIRECTION_INPUT);
	else if (ft_strchr(content, '>') && size == 1)
		token_add_flag(flag_arr, REDIRECTION_OUTPUT);
	else if (ft_strnstr(content, "<<", size) && size == 2)
		token_add_flag(flag_arr, REDIRECTION_DELIMITER);
	else if (ft_strnstr(content, ">>", size) && size == 2)
		token_add_flag(flag_arr, REDIRECTION_APPEND);
	return (flag_arr);
}

t_flag	*init_token_flags(t_token *token)
{
	t_flag	*flag_arr;
	int		size;
	char	*content;

	flag_arr = init_empty_token_flags();
	if (token == NULL || flag_arr == NULL || token->content == NULL)
		return (NULL);
	content = token->content;
	size = ft_strlen(content);
	if (ft_fully_delimiter(content) && size > 0 && token->handler == NONE)
		token_add_flag(flag_arr, DELIMITER);
	else if (token->handler == NONE && \
(((ft_strchr(content, '|') || ft_strchr(content, '<') || \
ft_strchr(content, '>')) && size == 1) || ((ft_strnstr(content, ">>", size) \
|| ft_strnstr(content, "<<", size)) && size == 2)))
		return (add_operator_flags(flag_arr, content, size));
	else if (!(size == 0 && token->handler == NONE))
	{
		token_add_flag(flag_arr, WORD);
		if (is_token_assignment(content) == TRUE && token->handler == NONE)
			token_add_flag(flag_arr, ASSIGNMENT);
	}
	return (flag_arr);
}

t_flag	*token_dup_flag(t_flag *flag_arr)
{
	t_flag	*new_flag_arr;
	int		i;

	if (flag_arr == NULL)
		return (NULL);
	new_flag_arr = init_empty_token_flags();
	if (new_flag_arr == NULL)
		return (NULL);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		new_flag_arr[i] = flag_arr[i];
		i++;
	}
	return (new_flag_arr);
}

int	token_add_flags_iter(t_lst *token_list, t_flag flag)
{
	t_lst	*head;
	t_token	*token;
	t_flag	*flags;

	if (token_list == NULL)
		return (1);
	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		flags = init_token_flags(token);
		if (has_token_flag(flags, DELIMITER) == FALSE)
		{
			if (token_add_flag(token->flags, flag) != 0)
			{
				free(flags);
				return (1);
			}
		}
		free(flags);
		head = head->next;
	}
	return (0);
}

int	apply_token_flags(t_lst	*token_list)
{
	t_lst	*head;
	t_token	*token;
	t_flag	*free_ptr;

	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		if (is_token_flags_empty(token->flags) == TRUE)
		{
			free_ptr = token->flags;
			token->flags = init_token_flags(token);
			free(free_ptr);
		}
		head = head->next;
	}
	return (0);
}
