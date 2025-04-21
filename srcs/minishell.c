/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/21 17:17:50 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_data	*data;

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
	ft_clear_history();
	// if (find_cmd_path("abc", envp) == NULL)
	// 	printf("NULL\n");
	// else
	// 	printf("%s\n", find_cmd_path("abc", envp));
	// execve(find_cmd_path("echo", envp), argv, envp);
}