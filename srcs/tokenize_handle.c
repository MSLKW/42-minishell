/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:07:35 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/14 15:25:26 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*tokenize_str(char *line)
{
	int		index;
	t_lst	*token_list;

	index = 0;
	token_list = NULL;
	while (line[index] != '\0')
	{
		if (line[index] == '\"')
			ft_lstadd_back(&token_list, ft_lstnew(handle_dquote(line, &index)));
		else if (line[index] == '\'')
			ft_lstadd_back(&token_list, ft_lstnew(handle_squote(line, &index)));
		else
			ft_lstadd_back(&token_list, ft_lstnew(handle_none(line, &index)));
	}
	return (token_list);
}

t_token	*handle_dquote(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	size = 0;
	(*index)++;
	while (line[*index + size] != '\"')
		size++;
	content = ft_substr(line, *index, size);
	if (content == NULL)
		return (NULL);
	token = init_token(content, DQUOTE, NULL);
	free(content);
	if (token == NULL)
		return (NULL);
	(*index) += size + 1;
	return (token);
}

t_token	*handle_squote(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	size = 0;
	(*index)++;
	while (line[*index + size] != '\'')
		size++;
	content = ft_substr(line, *index, size);
	if (content == NULL)
		return (NULL);
	token = init_token(content, SQUOTE, NULL);
	free(content);
	if (token == NULL)
		return (NULL);
	(*index) += size + 1;
	return (token);
}

// static int	handle_none_get_size(char *line, int index)
// {
	
// }

t_token	*handle_none(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	size = 0;
	if (ft_is_delimiter(line[*index + size]))
	{
		while (ft_is_delimiter(line[*index + size]))
			size++;
	}
	else if (line[*index + size] == '|' || line[*index + size] == '<' || line[*index + size] == '>')
	{
		while ((line[*index + size] == '|' || line[*index + size] == '<' || line[*index + size] == '>') && line[*index + size] != '\0')
			size++;
	}
	else if (line[*index + size] == '$')
	{
		size++;
		while ((ft_isalnum(line[*index + size]) == TRUE || line[*index + size] == '_' || line[*index + size] == '?') && line[*index + size] != '\0')
			size++;
	}
	else
	{
		while (ft_is_delimiter(line[*index + size]) == FALSE && line[*index + size] != '\"' && line[*index + size] != '\'' && line[*index + size] != '|' && line[*index + size] != '<' && line[*index + size] != '>' && line[*index + size] != '$'&& line[*index + size] != '\0')
			size++;
	}
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
