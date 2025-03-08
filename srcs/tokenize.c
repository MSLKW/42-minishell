/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:46:49 by maxliew           #+#    #+#             */
/*   Updated: 2025/03/08 18:35:29 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*tokenize_line(char *line)
{
	int	index;
	t_list	*token_list;

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
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	while (line[*index + size] != '\"')
		size++;
	content = ft_substr(line, *index, size);
	if (content == NULL || ft_strlen(content) == 0)
		return (NULL);
	token->content = content;
	token->handler = DQUOTE;
	token->type = get_token_type(content);
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
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	while (line[*index + size] != '\'')
		size++;
	content = ft_substr(line, *index, size);
	if (content == NULL || ft_strlen(content) == 0)
		return (NULL);
	token->content = content;
	token->handler = SQUOTE;
	token->type = get_token_type(content);
	(*index) += size + 1;
	return (token);
}

t_token	*handle_none(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	size = 0;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (line[*index + size] == ' ')
	{
		while (line[*index + size] == ' ')
			size++;
	}
	else
	{
		while (line[*index + size] != ' ' && line[*index + size] != '\"' && line[*index + size] != '\'' && line[*index + size] != '\0')
			size++;
	}
	content = ft_substr(line, *index, size);
	if (content == NULL || ft_strlen(content) == 0)
		return (NULL);
	token->content = content;
	token->handler = NONE;
	token->type = get_token_type(content);
	(*index) += size;
	return (token);
}

enum token_type	get_token_type(char *content)
{
	int	size;
	int	index;

	size = ft_strlen(content);
	index = 0;
	if (size == 0)
		return (ERROR);
	if (content[index] == ' ')
		return (WHITESPACE);
	else if (ft_strchr(content, '='))
		return (SET_VALUE); // variable needs to be alpha, value can be alphanumeric
	else if (ft_strchr(content, '|') && size == 1)
		return (PIPE);
	else if (ft_strchr(content, '<') && size == 1)
		return (REDIRECTION_INPUT);
	else if (ft_strchr(content, '>') && size == 1)
		return (REDIRECTION_OUTPUT);
	else if (ft_strnstr(content, ">>", size) && size == 2)
		return (REDIRECTION_APPEND);
	else if (ft_strnstr(content, "<<", size) && size == 2)
		return (REDIRECTION_DELIMITER);
	else if (size >= 2 && content[0] == '$' && ft_isalpha_str(content + 1) == TRUE)
		return (VARIABLE);
	else if (ft_isalnum_str(content) == TRUE)
		return (ALPHANUMERIC);
	return (ASCII);
}
