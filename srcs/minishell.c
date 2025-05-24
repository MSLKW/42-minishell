/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/24 20:40:00 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_data	*data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrlc_handler);
	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (1);
	data->argc = argc;
	data->argv = argv;
	data->envp = get_envp_copy(envp);
	data->env_var_lst = ft_lstnew(NULL);
	while(1)
	{
		line = ft_get_line();
		if (line && *line)
		{
			add_history(line);
			store_history(data, line);
		}
		t_lst *tokens = tokenize_line(line, data);
		debug_token_list(tokens);
		t_ast *ast_node = init_ast(&tokens);
		ft_printf("----- AST TREE -----\n");
		display_ast_tree(ast_node);
		free(line);
		execute_ast(ast_node, data);
	}
	rl_clear_history();
}

char	**get_envp_copy(char **envp)
{
	char **envp_copy;
	int i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	envp_copy = malloc(sizeof(char *) * (i + 1));
	if (envp_copy == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i] = NULL;
	return (envp_copy);
}
