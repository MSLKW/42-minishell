/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by maxliew           #+#    #+#             */
/*   Updated: 2025/02/27 23:32:24 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_line(void)
{
	char	*concat_line;
	char	*line_read;
	char	*temp;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	rl_on_new_line();
	concat_line = readline(ft_strjoin(cwd, "$ "));
	while (is_line_quote_ended(concat_line) == false)
	{
		rl_on_new_line();
		line_read = readline(">");
		temp = ft_strjoin(concat_line, line_read);
		free(concat_line);
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

t_list	*arg_split(char *line)
{
	int		index;
	int		start_index;
	int		quote_flag; // 0 is nothing | 1 is single | 2 is double
	t_list	*args;
	
	args = ft_lstnew(NULL);
	quote_flag = 0;
	index = 0;
	start_index = index;
	while (line[index] != '\0')
	{
		if (quote_flag == 0 && line[index] == ' ')
		{
			ft_lstadd_back(&args, ft_lstnew(ft_substr(line, start_index, index - start_index)));
			start_index = index;
		}
		else if (line[index] == '\'')
		{
			quote_flag = 1;
			// iterate until we find the next single quote
		}
		else if (line[index] == '\"')
		{
			quote_flag = 2;

		}
		index++;
	}
	return (args);
}

// echo "h"      "i"
// h i

// echo "h" "i"
// h i

// echo "h""i"
// hi

//  