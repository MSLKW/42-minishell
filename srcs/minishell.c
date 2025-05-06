/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/06 16:37:46 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_data	*data;
	const char	*history_file;

	history_file = "minishell_history";
	signal(SIGINT, ctrlc_handler);
	data = ft_calloc(1, sizeof(data));
	if (data == NULL)
		return (1);
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;

	while(1)
	{
		line = ft_get_line();
		t_lst *tokens = tokenize_line(line, data);
		debug_token_list(tokens);
		t_ast *ast_node = init_ast(&tokens);
		ft_printf("----- AST TREE -----\n");
		display_ast_tree(ast_node);
		free(line);
		ft_show_history();
	}
	write_history(history_file);
	rl_clear_history();
	// if (find_cmd_path("abc", envp) == NULL)
	// 	printf("NULL\n");
	// else
	// 	printf("%s\n", find_cmd_path("abc", envp));
	// execve(find_cmd_path("echo", envp), argv, envp);
}