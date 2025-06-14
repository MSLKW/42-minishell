/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:08:50 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/14 15:30:11 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	has_token_flag(t_flag *flags, t_flag flag)
{
	int	i;

	if (flags == NULL)
		return (FALSE);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flags[i] == flag)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_flag	*init_empty_token_flags(void)
{
	t_flag *flag_arr;

	flag_arr = ft_calloc(TOKEN_FLAG_SIZE, sizeof(t_flag));
	if (flag_arr == NULL)
		return (NULL);
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
	// printf("ft_is_delimiter: %i\n", ft_fully_delimiter(content));
	if (size == 0 && token->handler == NONE)
	{
		// do nothing
	}
	else if (ft_fully_delimiter(content) && size > 0 && token->handler == NONE)
	{
		token_add_flag(flag_arr, DELIMITER);
	}
	else if (token->handler == NONE && (((ft_strchr(content, '|') || ft_strchr(content, '<') || ft_strchr(content, '>')) && size == 1) || ((ft_strnstr(content, ">>", size) || ft_strnstr(content, "<<", size)) && size == 2)))
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
	}
	else
	{
		token_add_flag(flag_arr, WORD);
		if (is_token_assignment(content) == TRUE && token->handler == NONE)
			token_add_flag(flag_arr, ASSIGNMENT);
	}
	return (flag_arr);
}

/*
	Returns 0 on success
	Returns 1 on input error
	Returns 2 if no space in flag_arr
*/
int	token_add_flag(t_flag *flag_arr, t_flag flag)
{
	int	i;

	if (flag_arr == NULL || flag == NO_FLAG)
		return (1);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flag_arr[i] == NO_FLAG || flag_arr[i] == flag)
		{
			flag_arr[i] = flag;
			return (0);
		}
		i++;
	}
	return (2);
}

/*
	Returns 0 on success
	Returns 1 on input error
	Returns 2 if no space in flag_arr
*/
int	token_add_flags(t_flag *flag_arr, t_flag *new_flag_arr)
{
	int	i;

	if (flag_arr == NULL || new_flag_arr == NULL)
		return (1);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (has_token_flag(flag_arr, new_flag_arr[i]) == FALSE)
		{
			if (token_add_flag(flag_arr, new_flag_arr[i]) == 2)
				return (2);
		}
		i++;
	}
	return (0);
}
/*
	Returns 0 on success, Returns 1 on error
*/
int	token_rm_flag(t_flag *flag_arr, t_flag flag)
{
	int	i;
	int	success;

	if (flag_arr == NULL || flag == NO_FLAG)
		return (1);
	success = 1;
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flag_arr[i] == flag)
		{
			flag_arr[i] = NO_FLAG;
			success = 0;
		}
		i++;
	}
	return (success);
}

int	token_rm_flags(t_flag *flag_arr)
{
	int	i;

	if (flag_arr == NULL)
		return (1);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		flag_arr[i] = NO_FLAG;
		i++;
	}
	return (0);
}

t_flag	*token_dup_flag(t_flag *flag_arr)
{
	t_flag	*new_flag_arr;

	int	i;

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

t_bool	is_token_flags_empty(t_flag *flags_arr)
{
	int	i;

	if (flags_arr == NULL)
		return (TRUE);
	i = 0;
	while (i < TOKEN_FLAG_SIZE)
	{
		if (flags_arr[i] != NO_FLAG)
			return (FALSE);
		i++;
	}
	return (TRUE);
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

int	count_token_with_flag(t_lst	*token_list, t_flag flag)
{
	int		count;
	t_lst	*head;
	t_token	*token;

	if (token_list == NULL)
		return (-1);
	count = 0;
	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		if (has_token_flag(token->flags, flag) == TRUE)
			count++;
		head = head->next;
	}
	return (count);
}
