/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:12:35 by zernest           #+#    #+#             */
/*   Updated: 2025/05/30 12:41:19 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	execute_ast(t_ast *ast, t_data *data)
// {
// 	if (!ast)
// 		return (1);
// 	if (ast->token->primary_type == SET_VALUE)
// 		return (execute_setvalue(ast, data));
// 	return (execute_command(ast, data));
// }

int	execute_ast(t_ast *ast, t_data *data)
{
	t_token *token;

	if (!ast || !ast->token)
		return (1);

	token = (t_token *)ast->token;

	if (token->primary_type == PIPE)
		return (execute_pipeline(ast, data));
	// else if (token->primary_type == REDIRECTION)
	// 	return (execute_redirection(ast)); // later
	else if (token->secondary_type == COMMAND)
		return (execute_command(ast, data));
	else if (token->primary_type == SET_VALUE)
		return (execute_setvalue(ast, data)); // like export/assign
	else
		return (1);
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
		printf("cmd_path: %s\n", cmd_path);
		if (cmd_path != NULL)
		{
			execve(cmd_path, args, data->envp);
		}
		if (get_env_var_value("PATH", data->env_var_lst) == NULL)
			printf("%s: No such file or directory\n", args[0]);
		else
			printf("%s: command not found\n", args[0]);
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

// int	prepare_args_and_redirect(t_ast *ast, char **args) DOESNT WORK
// {
// 	t_lst	*node;
// 	int		fd;
// 	int		i = 0;

// 	node = ast->node_list;
// 	while (node)
// 	{
// 		t_token *tok = (t_token *)node->content;
// 		if (tok->primary_type == REDIRECTION)
// 		{
// 			node = node->next;
// 			if (!node)
// 				return (ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2), -1);
// 			t_token *file_tok = (t_token *)node->content;
// 			fd = open(file_tok->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd < 0)
// 				return (perror("open"), -1);
// 			dup2(fd, STDOUT_FILENO);
// 			close(fd);
// 			node = node->next;
// 			continue;
// 		}
// 		args[i++] = tok->content;
// 		node = node->next;
// 	}
// 	args[i] = NULL;
// 	return (0);
// }

int execute_pipeline(t_ast *pipe_node, t_data *data)
{
	int pipe_fd[2];
	pid_t pid1, pid2;

	if (!pipe_node || ft_lstsize(pipe_node->node_list) != 2)
		return (1);
	t_ast *left = (t_ast *)pipe_node->node_list->content;
	t_ast *right = (t_ast *)pipe_node->node_list->next->content;
	if (pipe(pipe_fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	// left side
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		exit(execute_ast(left, data));
	}
	// right side
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		exit(execute_ast(right, data));
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (0);
}
