/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/03/04 20:56:16 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;

	while(1)
	{
		line = ft_get_line();
		ft_printf("tokenize_line\n");
		t_list *tokens = tokenize_line(line);
		ft_printf("debug_token_list\n");
		debug_token_list(tokens);
		free(line);
		ft_show_history();
	}
	ft_clear_history();
}