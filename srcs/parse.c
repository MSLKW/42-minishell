/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/18 11:47:05 by maxliew          ###   ########.fr       */
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
	int index = 0;
	while (is_line_quote_ended(concat_line, FALSE, &index) == FALSE)
	{
		rl_on_new_line();
		line_read = readline(">");
		new_line_read = ft_strjoin("\n", line_read);
		temp = ft_strjoin(concat_line, new_line_read);
		free(concat_line);
		free(new_line_read);
		free(line_read);
		concat_line = temp;
		ft_printf("line: \"%s\"\n", concat_line);
		index = 0;
	}
	add_history(concat_line);
	return (concat_line);
}

t_bool	is_line_quote_ended(char *line, t_bool is_subshell, int *index)
{
	int	quote_flag;
	int	parenthesis_count;

	quote_flag = 0;
	parenthesis_count = 0;
	while (line[*index] != '\0')
	{
		if (is_subshell == TRUE && parenthesis_count == -1)
			break;
		if (quote_flag == 0 && line[*index] == '\'')
			quote_flag = 1;
		else if (quote_flag == 1 && line[*index] == '\'')
			quote_flag = 0;
		else if (quote_flag == 0 && line[*index] == '\"')
			quote_flag = 2;
		else if (quote_flag == 2 && line[*index] == '\"')
			quote_flag = 0;
		else if (quote_flag == 0 && line[*index] == '(')
			parenthesis_count++;
		else if (quote_flag == 0 && line[*index] == ')')
			parenthesis_count--;
		else if (ft_strlen(line) != 1 && (quote_flag != 1 && line[*index] == '$' && line[*index + 1] == '('))
		{
			(*index) += 2;
			if (is_line_quote_ended(line, TRUE, index) == FALSE)
				return (FALSE);
			continue;
		}
		(*index)++;
	}
	// debugger
	// ft_printf("index: %i | subshell = %i | quote_flag = %i | parenthesis_count = %i | line: \"%s\"\n", *index, is_subshell, quote_flag, parenthesis_count, line);
	if (is_subshell == TRUE && quote_flag == 0 && parenthesis_count == -1)
		return (TRUE);
	else if (is_subshell == FALSE && quote_flag == 0 && parenthesis_count == 0)
		return (TRUE);
	return (FALSE);
}