/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:08:50 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/01 14:21:56 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// enum token_flag	operator_token_flag(char *content, int size)
// {
	
// }

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

t_flag	*init_token_flags(char *content)
{
	t_flag	*flag_arr;
	int		size;

	flag_arr = ft_calloc(sizeof(t_flag), TOKEN_FLAG_SIZE);
	if (flag_arr == NULL || content == NULL)
		return (NULL);
	size = ft_strlen(content);
	if (size == 0)
		token_add_flag(flag_arr, EMPTY);
	else if (content[0] == ' ' && size > 0)
	{
		token_add_flag(flag_arr, DELIMITER);
		token_add_flag(flag_arr, WHITESPACE);
	}
	else if (((ft_strchr(content, '|') || ft_strchr(content, '<') || ft_strchr(content, '>')) && size == 1) || ((ft_strnstr(content, ">>", size) || ft_strnstr(content, "<<", size)) && size == 2))
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
		if (is_token_assignment(content) == TRUE)
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
		if (flag_arr[i] == NO_FLAG)
		{
			flag_arr[i] = flag;
			return (0);
		}
		i++;
	}
	return (2);
}

t_flag	*token_dup_flag(t_flag *flag_arr)
{
	t_flag	*new_flag_arr;

	int	i;

	if (flag_arr == NULL)
		return (NULL);
	new_flag_arr = ft_calloc(sizeof(t_flag), TOKEN_FLAG_SIZE);
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
