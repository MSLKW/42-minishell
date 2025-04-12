/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/12 22:42:10 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;

	(void)argc;
	(void)argv;
	(void)envp;
	while(1)
	{
		line = ft_get_line();
		t_lst *tokens = tokenize_line(line);
		t_ast *ast_node = find_pipes(tokens);
		ft_printf("----- AST TREE -----\n");
		display_ast_tree(ast_node);
		debug_token_list(tokens);
		free(line);
		ft_show_history();
	}
	ft_clear_history();
	// printf("%s\n", find_cmd_path("echo", envp));
	// execve(find_cmd_path("echo", envp), argv, envp);
}