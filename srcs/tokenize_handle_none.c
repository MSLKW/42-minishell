/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle_none.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 01:56:20 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 01:56:28 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_bool	is_char_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static t_bool	is_char_end(char c)
{
	return (ft_is_delimiter(c) == FALSE && c != '\"' && c != '\'' \
&& c != '|' && c != '<' && c != '>' && c != '$');
}

static t_bool	char_val(char c)
{
	return (ft_isalnum(c) == TRUE || c == '_' || c == '?');
}

static int	handle_none_get_size(char *line, int *index)
{
	int		size;

	size = 0;
	if (ft_is_delimiter(line[*index + size]))
	{
		while (ft_is_delimiter(line[*index + size]))
			size++;
	}
	else if (is_char_op(line[*index + size]))
	{
		while (is_char_op(line[*index + size]) && line[*index + size] != '\0')
			size++;
	}
	else if (line[*index + size] == '$')
	{
		size++;
		while (char_val(line[*index + size]) && line[*index + size] != '\0')
			size++;
	}
	else
	{
		while (is_char_end(line[*index + size]) && line[*index + size] != '\0')
			size++;
	}
	return (size);
}

t_token	*handle_none(char *line, int *index)
{
	int		size;
	t_token	*token;
	char	*content;

	size = handle_none_get_size(line, index);
	content = ft_substr(line, *index, size);
	if (content == NULL)
		return (NULL);
	token = init_token(content, NONE, NULL);
	free(content);
	if (token == NULL)
		return (NULL);
	(*index) += size;
	return (token);
}
