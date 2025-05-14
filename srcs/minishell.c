/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/14 20:46:50 by maxliew          ###   ########.fr       */
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
	data->env_var_lst = ft_lstnew(NULL);
	while(1)
	{
		line = ft_get_line();
		if (line[0] != '\0')
			add_history(line);
		t_lst *tokens = tokenize_line(line, data);
		debug_token_list(tokens);
		t_ast *ast_node = init_ast(&tokens);
		ft_printf("----- AST TREE -----\n");
		display_ast_tree(ast_node);
		free(line);
		ft_show_history();
		execute_ast(ast_node, data);
	}
	write_history(history_file);
	rl_clear_history();
}


// int	main(int argc, char *argv[], char *envp[])
// {
// 	t_data	*data;
	
// 	(void)argc;
// 	(void)argv;
// 	(void)envp;
// 	data = ft_calloc(1, sizeof(t_data));
// 	if (data == NULL)
// 		return (1);
// 	data->env_var_lst = ft_lstnew(NULL);
// 	set_env_variable(data->env_var_lst, init_env_variable(".bc", "123"));
// 	set_env_variable(data->env_var_lst, init_env_variable("sigh", "fight"));
// 	set_env_variable(data->env_var_lst, init_env_variable(".tight", "bye"));
// 	set_env_variable(data->env_var_lst, init_env_variable("a5", "6"));
// 	set_env_variable(data->env_var_lst, init_env_variable("hey", "hello"));
// 	display_env_var(data);
// 	unset_env_variable("a5", &data->env_var_lst);
// 	printf("\n");
// 	display_env_var(data);
// 	t_env_var *env_var = get_env_variable("hey", data->env_var_lst);
// 	if (env_var == NULL)
// 	{
// 		printf("env_var is null\n");
// 		return (1);
// 	}
// 	printf("main | env_var key: %s | val: %s\n", env_var->key, env_var->value);
// }
