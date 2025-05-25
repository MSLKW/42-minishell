/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/25 22:25:37 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrlc_handler);
	data = init_data(argc, argv, envp);
	if (data == NULL)
		return (1);
	while (1)
	{
		shell_routine(data);
	}
	rl_clear_history();
}

void	shell_routine(t_data *data)
{
	char	*line;
	t_lst	*tokens;
	t_ast	*ast_node;

	line = ft_get_line();
	if (line && *line)
	{
		add_history(line);
		store_history(data, line);
	}
	tokens = tokenize_line(line, data);
	debug_token_list(tokens);
	ast_node = init_ast(&tokens);
	ft_printf("----- AST TREE -----\n");
	display_ast_tree(ast_node);
	free(line);
	data->last_exit_code = execute_ast(ast_node, data);
}

t_data	*init_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->argc = argc;
	data->argv = argv;
	data->envp = get_envp_copy(envp);
	data->env_var_lst = init_exported_env_var_lst(data->envp);
	return (data);
}

t_lst	*init_exported_env_var_lst(char **envp)
{
	t_lst	*result;
	t_env_var	*env_var;
	int		i;

	if (envp == NULL || envp[0] == NULL)
		return (ft_lstnew(NULL));
	i = 0;
	result = ft_lstnew(NULL);
	while (envp[i] != NULL)
	{
		env_var = split_setvalue(envp[i]);
		if (env_var != NULL)
		{
			env_var = set_env_variable(result, env_var, envp);
			env_var->is_export = TRUE;
		}
		i++;
	}
	return (result);
}

char	**get_envp_copy(char **envp)
{
	char	**envp_copy;
	int		i;

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
