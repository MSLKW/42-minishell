/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/07 22:55:34 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_data	*data;
	const char	*history_file;

	signal(SIGQUIT, SIG_IGN);
	history_file = "minishell_history";

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
		if (line[0] != '\0')
			add_history(line);
		t_lst *tokens = tokenize_line(line, data);
		debug_token_list(tokens);
		t_ast *ast_node = init_ast(&tokens);
		execute_ast(ast_node, data);
		ft_printf("----- AST TREE -----\n");
		display_ast_tree(ast_node);
		execute_cmd(ast_node, data);
		free(line);
		ft_show_history();
	}
	write_history(history_file);
	rl_clear_history();
}
