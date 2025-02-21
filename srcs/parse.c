/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by maxliew           #+#    #+#             */
/*   Updated: 2025/02/21 13:56:52 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_line(void)
{
	rl_on_new_line();
	char *line_read = readline(NULL);
	add_history(line_read);
	return (line_read);
}

t_list	*arg_split(char *line)
{
	int		index;
	int		start_index;
	int		quote_flag; // 0 is nothing | 1 is single | 2 is double
	t_list	*args;
	
	args = ft_lstnew(NULL);
	index = 0;
	start_index = index;
	while (line[index] != '\0')
	{
		if (line[index] == ' ')
		{
			ft_lstadd_back(&args, ft_lstnew(ft_substr(line, start_index, index - start_index)));
			start_index = index;
		}
		else if (line[index] == '\'')
		{
			quote_flag = 1;
			
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