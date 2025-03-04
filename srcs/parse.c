/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by maxliew           #+#    #+#             */
/*   Updated: 2025/03/04 21:11:11 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// can't get new lines when finishing quote
char	*ft_get_line(void)
{
	char	*concat_line;
	char	*line_read;
	char	*new_line_read;
	char	*temp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	rl_on_new_line();
	concat_line = readline(ft_strjoin(cwd, "$ "));
	while (is_line_quote_ended(concat_line) == false)
	{
		rl_on_new_line();
		line_read = readline(">");
		new_line_read = ft_strjoin("\n", line_read);
		temp = ft_strjoin(concat_line, new_line_read);
		free(concat_line);
		free(new_line_read);
		free(line_read);
		concat_line = temp;
	}
	add_history(concat_line);
	return (concat_line);
}

t_bool	is_line_quote_ended(char *line)
{
	int	index;
	int	quote_flag;

	index = 0;
	quote_flag = 0;
	while (line[index] != '\0')
	{
		if (quote_flag == 0 && line[index] == '\'')
			quote_flag = 1;
		else if (quote_flag == 1 && line[index] == '\'')
			quote_flag = 0;
		else if (quote_flag == 0 && line[index] == '\"')
			quote_flag = 2;
		else if (quote_flag == 2 && line[index] == '\"')
			quote_flag = 0;
		index++;
	}
	if (quote_flag == 0)
		return (true);
	return (false);
}

t_list	*tokenize_line(char *line)
{
	int	index;
	t_list	*token_list;

	index = 0;
	token_list = ft_lstnew(NULL);
	ft_printf("start_loop\n");
	while (line[index] != '\0')
	{
		ft_printf("loop_tokenize_line\n");
		if (line[index] == '\"')
		{
			ft_printf("dquote\n");
			ft_lstadd_back(&token_list, ft_lstnew(handle_dquote(line, &index)));
		}
		else if (line[index] == '\'')
		{
			ft_printf("squote\n");
			ft_lstadd_back(&token_list, ft_lstnew(handle_squote(line, &index)));
		}
		else
		{
			ft_printf("none");
			ft_lstadd_back(&token_list, ft_lstnew(handle_none(line, &index)));
		}
		index++;
	}
	return (token_list);
}

t_token	*handle_dquote(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	ft_printf("handle_dquote\n");
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
	token->type = ALPHANUMERIC; //get_token_type(token->content);
	(*index) += size + 1;
	return (token);
}

t_token	*handle_squote(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	ft_printf("handle_squote\n");
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
	token->type = ALPHANUMERIC; //get_token_type(token->content);
	(*index) += size + 1;
	return (token);
}

t_token	*handle_none(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	ft_printf("handle_none\n");
	size = 0;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	ft_printf("counting size %i\n", *index);
	if (line[*index + size] == ' ')
	{
		while (line[*index + size] == ' ')
			size++;
	}
	else
	{
		ft_printf("line: \"%s\"\n", line);
		ft_printf("chr: %c\n", line[*index + size]);
		while (line[*index + size] != ' ' && line[*index + size] != '\0')
		{
			ft_printf("size++\n");
			size++;
		}
	}
	ft_printf("taking str\n");
	content = ft_substr(line, *index, size);
	if (content == NULL || ft_strlen(content) == 0)
		return (NULL);
	token->content = content;
	token->handler = NONE;
	token->type = ALPHANUMERIC; //get_token_type(token->content);
	(*index) += size + 1;
	ft_printf("finished\n");
	return (token);
}

void	debug_token_list(t_list *token_list)
{
	t_list	*head;

	printf("debug_token_list");
	head = token_list;
	while (head != NULL)
	{
		t_token	*token = head->content;
		if (token == NULL)
		{
			printf("NULL\n");
			head = head->next;
			continue;
		}
		printf("Token | content->%s | handler->%i | type->%i\n", token->content, token->handler, token->type);
		head = head->next;
	}
}
