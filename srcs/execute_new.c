/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:12:35 by zernest           #+#    #+#             */
/*   Updated: 2025/05/26 18:31:29 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_ast *ast, t_data *data)
{
	if (!ast)
		return (1);
	if (ast->token->primary_type == SET_VALUE)
		return (execute_setvalue(ast, data));
	return (execute_command(ast, data));
}

// char	**build_cmd_args(t_ast *node)
// {
// 	int		count;
// 	t_lst	*cur;
// 	t_token	*tok;
// 	char	**args;
// 	int		i;

// 	count = 0;
// 	cur = node->node_list;
// 	while (cur)
// 	{
// 		tok = (t_token *)cur->content;
// 		if (tok->secondary_type == COMMAND || tok->secondary_type == ARGUMENT)
// 			count++;
// 		cur = cur->next;
// 	}
// 	args = malloc(sizeof(char *) * (count + 1));
// 	if (!args)
// 		return (NULL);
// 	cur = node->node_list;
// 	i = 0;
// 	while (cur)
// 	{
// 		tok = (t_token *)cur->content;
// 		if (tok->secondary_type == COMMAND || tok->secondary_type == ARGUMENT)
// 		{
// 			printf("Adding arg: %s (type: %d)\n", tok->content, tok->secondary_type);
// 			args[i++] = tok->content;
// 		}
// 		cur = cur->next;
// 	}
// 	args[i] = NULL;
// 	for (int j = 0; j < i; j++)
// 		printf("TEEESTTarg[%d]: %s\n", j, args[j]);
// 	return (args);
// }

char **build_cmd_args(t_ast *cmd_node)
{
	int		count;
	char	**args;
	t_lst	*cur;
	int		i = 0;

	if (!cmd_node)
		return (NULL);
	count = ft_lstsize(cmd_node->node_list);
	args = malloc(sizeof(char *) * (count + 2)); // +1 for command, +1 for NULL
	if (!args)
		return (NULL);
	if (cmd_node->token)
		args[i++] = ft_strdup(((t_token *)cmd_node->token)->content);
	cur = cmd_node->node_list;
	while (cur)
	{
		t_ast *child = (t_ast *)cur->content;
		if (child && child->token)
			args[i++] = ft_strdup(((t_token *)child->token)->content);
		cur = cur->next;
	}
	args[i] = NULL;
	return (args);
}

int	execute_command(t_ast *node, t_data *data)
{
	char	**args;
	pid_t	pid;
	char	*cmd_path;
	int		status;

	args = build_cmd_args(node);
	
	for (int i = 0; args && args[i]; i++)
		printf("arg[%d] = \"%s\"\n", i, args[i]);
	printf("Executing command: %s\n", args[0]);
	status = -1;
	if (!args || !args[0])
		return (1);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		status = builtin_pwd();
	if (ft_strncmp(args[0], "echo", 5) == 0)
		status = builtin_echo(args);
	if (ft_strncmp(args[0], "cd", 3) == 0)
		status = builtin_cd(args + 1, data);
	if (ft_strncmp(args[0], "env", 4) == 0)
		status = builtin_env(data->envp);
	if (ft_strncmp(args[0], "exit", 5) == 0)
		status = builtin_exit(args, data);
	if (ft_strncmp(args[0], "unset", 6) == 0)
		status = builtin_unset_env(args[1], &data->envp, &data->env_var_lst);
	if (ft_strncmp(args[0], "export", 7) == 0)
		status = builtin_export(args, &data->envp, data);
	if (ft_strncmp(args[0], "history", 8) == 0)
		status = builtin_history(data);
	if (status != -1)
	{
		free_str_arr(args);
		free_tokens(&data->free_ptr_tokens);
		free_ast(&data->free_ptr_ast);
		return (status);
	}
	printf("Last exit code: %d\n", data->last_exit_code);
	pid = fork();
	if (pid == 0)
	{
		if (is_token_executable(args[0]) == TRUE)
			cmd_path = args[0];
		else
			cmd_path = find_cmd_path(args[0], data->env_var_lst);
		if (cmd_path != NULL)
		{
			execve(cmd_path, args, data->envp);
		}
		if (get_env_var_value("PATH", data->env_var_lst) == NULL)
			printf("%s: No such file or directory\n", args[0]);
		else
			ft_printf("%s: command not found\n", args[0]);
		// perror("execve");
		free_str_arr(args);
		free_exit(127, data);
	}
	else
		waitpid(pid, &status, 0);
	free_tokens(&data->free_ptr_tokens);
	free_ast(&data->free_ptr_ast);
	free_str_arr(args);
	return (WEXITSTATUS(status));
}

int	execute_setvalue(t_ast *node, t_data *data)
{
	t_env_var *env_var;
	t_ast		*arg_node;
	
	env_var = split_setvalue(node->token->content);
	if (env_var == NULL || env_var->key == NULL)
		return (1);
	else if (env_var->value == NULL || ft_strlen(env_var->value) == 0)
	{
		if (node->node_list != NULL && node->node_list->content != NULL)
		{
			arg_node = node->node_list->content;
			free(env_var->value);
			env_var->value = ft_strdup(arg_node->token->content);
		}
	}
	set_env_variable(data->env_var_lst, env_var, &data->envp);
	free_tokens(&data->free_ptr_tokens);
	free_ast(&data->free_ptr_ast);
	return (0);
}