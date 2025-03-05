/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by maxliew           #+#    #+#             */
/*   Updated: 2025/03/05 10:47:27 by maxliew          ###   ########.fr       */
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
	while (is_line_quote_ended(concat_line) == FALSE)
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
		return (TRUE);
	return (FALSE);
}

void	debug_token_list(t_list *token_list)
{
	t_list	*head;

	head = token_list;
	while (head != NULL)
	{
		t_token	*token = head->content;
		if (token == NULL)
		{
			printf("NULL detected in token_list\n");
			head = head->next;
			continue;
		}
		printf("Token | content-> \"%s\" | handler-> %i | type-> %i\n", token->content, token->handler, token->type);
		head = head->next;
	}
}
