/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/18 16:20:22 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_data	*data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrlc_handler);
	data = ft_calloc(1, sizeof(data));
	if (data == NULL)
		return (1);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	// data->env_var = NULL;
	while(1)
	{
		line = ft_get_line();
		if (line && *line)
			add_history(line);
		t_lst *tokens = tokenize_line(line, data);
		debug_token_list(tokens);
		t_ast *ast_node = init_ast(&tokens);
		execute_ast(ast_node, data);
		ft_printf("----- AST TREE -----\n");
		display_ast_tree(ast_node);
		free(line);
	} 
	rl_clear_history();
}
