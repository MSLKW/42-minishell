/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:12:35 by zernest           #+#    #+#             */
/*   Updated: 2025/05/22 15:46:01 by maxliew          ###   ########.fr       */
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
	if (!args || !args[0])
		return (1);
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (builtin_echo(args));
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (builtin_cd(args + 1));
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (builtin_env(data->envp));
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (builtin_exit(args));
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (builtin_unset_env(args[1], &data->envp));
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (builtin_export(args, &data->envp, data));
	if (ft_strncmp(args[0], "history", 8) == 0)
		return (builtin_history(data));
	printf("Last exit code: %d", data->last_exit_code);
	pid = fork();
	if (pid == 0)
	{
		if (is_token_executable(args[0]) == TRUE)
		{
			cmd_path = args[0];
		}
		else
		{
			cmd_path = find_cmd_path(args[0], data->envp);
			if (!cmd_path)
			{
				ft_printf("command not found: %s\n", args[0]);
				exit (127);
			}
		}
		execve(cmd_path, args, data->envp);
		perror("execve");
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
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
	set_env_variable(data->env_var_lst, env_var);
	return (0);
}