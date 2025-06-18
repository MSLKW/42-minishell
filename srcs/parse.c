/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 16:43:42 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_line_reprompt(char *concat_line, t_data *data)
{
	int		index;
	char	*line_read;
	char	*new_line_read;
	char	*temp;

	index = 0;
	while (is_line_quote_ended(concat_line, FALSE, &index) == FALSE)
	{
		rl_on_new_line();
		line_read = readline("> ");
		if (!line_read)
		{
			free(concat_line);
			ctrld_handler(data);
		}
		new_line_read = ft_strjoin("\n", line_read);
		temp = ft_strjoin(concat_line, new_line_read);
		free(concat_line);
		free(new_line_read);
		free(line_read);
		concat_line = temp;
		index = 0;
	}
	return (concat_line);
}

char	*ft_get_line(t_data *data)
{
	char	*concat_line;
	char	*prompt;

	prompt = ft_get_prompt(data);
	rl_on_new_line();
	concat_line = readline(prompt);
	free(prompt);
	if (!concat_line)
		ctrld_handler(data);
	concat_line = ft_line_reprompt(concat_line, data);
	return (concat_line);
}

static int	quote_end_logic(char *line, int *q_flag, int *p_count, int *index)
{
	if (*q_flag == 0 && line[*index] == '\'')
		*q_flag = 1;
	else if (*q_flag == 1 && line[*index] == '\'')
		*q_flag = 0;
	else if (*q_flag == 0 && line[*index] == '\"')
		*q_flag = 2;
	else if (*q_flag == 2 && line[*index] == '\"')
		*q_flag = 0;
	else if (*q_flag == 0 && line[*index] == '(')
		(*p_count)++;
	else if (*q_flag == 0 && line[*index] == ')')
		(*p_count)--;
	else if (ft_strlen(line) != 1 && (*q_flag != 1 && \
line[*index] == '$' && line[*index + 1] == '('))
	{
		(*index) += 2;
		if (is_line_quote_ended(line, TRUE, index) == FALSE)
			return (2);
		return (1);
	}
	return (0);
}

t_bool	is_line_quote_ended(char *line, t_bool is_subshell, int *index)
{
	int	quote_flag;
	int	parenthesis_count;
	int	status;

	quote_flag = 0;
	parenthesis_count = 0;
	status = 0;
	while (line[*index] != '\0')
	{
		if (is_subshell == TRUE && parenthesis_count == -1)
			break ;
		status = quote_end_logic(line, &quote_flag, &parenthesis_count, index);
		if (status == 2)
			return (FALSE);
		else if (status == 1)
			continue ;
		(*index)++;
	}
	if (is_subshell == TRUE && quote_flag == 0 && parenthesis_count == -1)
		return (TRUE);
	else if (is_subshell == FALSE && quote_flag == 0 && parenthesis_count == 0)
		return (TRUE);
	return (FALSE);
}
