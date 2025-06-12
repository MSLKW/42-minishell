/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:55 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/12 15:02:54 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	*data;

	rl_catch_signals = 0;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ctrlc_handler);
	data = init_data(argc, argv, envp);
	if (data == NULL)
	{
		printf("Argument Error\n");
		return (1);
	}
	set_shlvl(data->env_var_lst, &data->envp);
	while (1)
	{
		shell_routine(data);
	}
	rl_clear_history();
	return (data->last_exit_code);
}

void	shell_routine(t_data *data)
{
	char	*line;
	t_lst	*tokens;
	t_ast	*ast_node;

	line = ft_get_line(data);
	if (line && *line)
	{
		add_history(line);
		store_history(data, line);
	}
	tokens = tokenize_line(line, data);
	data->free_ptr_tokens = tokens;
	debug_token_list(tokens);
	ast_node = init_ast(&tokens);
	data->free_ptr_ast = ast_node;
	ft_printf("----- AST TREE -----\n");
	display_ast_tree(ast_node);
	free(line);
	data->last_exit_code = execute_ast(ast_node, data);
	// free_tokens(&data->free_ptr_tokens);
	// free_ast(&data->free_ptr_ast);
}

t_data	*init_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->argc = argc;
	data->argv = argv;
	data->envp = get_envp_copy(envp, 0);
	data->env_var_lst = init_exported_env_var_lst(&data->envp);
	data->free_ptr_ast = NULL;
	data->free_ptr_tokens = NULL;
	return (data);
}

t_lst	*init_exported_env_var_lst(char ***envp)
{
	t_lst	*result;
	t_env_var	*env_var;
	int		i;

	if (envp == NULL || *envp == NULL || (*envp)[0] == NULL)
		return (ft_lstnew(NULL));
	i = 0;
	result = ft_lstnew(NULL);
	while ((*envp)[i] != NULL)
	{
		env_var = split_assignment((*envp)[i]);
		if (env_var != NULL)
		{
			env_var = set_env_variable(result, env_var, envp);
			env_var->is_export = TRUE;
		}
		i++;
	}
	return (result);
}

char	**get_envp_copy(char **envp, int extra)
{
	char	**envp_copy;
	int		i;

	if (envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
		i++;
	envp_copy = ft_calloc(i + extra + 1, sizeof(char *));
	if (envp_copy == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_copy[i + extra] = NULL;
	return (envp_copy);
}
