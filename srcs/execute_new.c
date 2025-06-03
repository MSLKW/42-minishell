/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:12:35 by zernest           #+#    #+#             */
/*   Updated: 2025/06/03 18:20:29 by zernest          ###   ########.fr       */
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

	if (has_token_flag(token->flags, PIPE))
		return (execute_pipeline(ast, data));
	// else if (has_token_flag(token->flags, REDIRECTION))
	// 	return (execute_redirection(ast)); // later
	// else if (has_token_flag(token->flags, REDIRECTION) && has_token_flag(token->flags, REDIRECTION_OUTPUT))
	// {
	// 	return execute_redirection_out(ast, data);
	// }
	else if (has_token_flag(token->flags, COMMAND))
		return (execute_command(ast, data));
	else if (has_token_flag(token->flags, ASSIGNMENT))
		return (execute_setvalue(ast, data)); // like export/assign
	else
		return (1);
}

// int execute_redirection_out(t_ast *node, t_data *data)
// {
// 	int fd;
// 	int saved_stdout;
// 	t_ast *left = node->left;
// 	t_ast *right = node->right;

// 	if (!left || !right)
// 		return (set_error("Invalid redirection syntax"), 1);

// 	fd = open(right->token->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		return (perror("open"), 1);
// 	saved_stdout = dup(STDOUT_FILENO);
// 	dup2(fd, STDOUT_FILENO);
// 	close(fd);
// 	int status = execute_ast(left, data);
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	close(saved_stdout);

// 	return status;
// }

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

// int handle_redirection(t_ast *redir_node, t_data *data) {
// 	printf("Handling redirection:\n");
//     if (!redir_node || !redir_node->node_list || 
//         ft_lstsize(redir_node->node_list) < 2) {
//         fprintf(stderr, "Syntax error near redirection\n");
//         return 1;
//     }

//     // Get the command and filename nodes
//     t_ast *cmd_node = (t_ast *)redir_node->node_list->content;
//     t_ast *file_node = (t_ast *)redir_node->node_list->next->content;

//     if (!cmd_node || !file_node || !file_node->token) {
//         fprintf(stderr, "Syntax error in redirection\n");
//         return 1;
//     }

//     // Open the output file
//     int fd = open(file_node->token->content, 
//                  O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd < 0) {
//         perror("minishell");
//         return 1;
//     }

//     // Save original stdout
//     int stdout_backup = dup(STDOUT_FILENO);
//     if (stdout_backup < 0) {
//         perror("minishell");
//         close(fd);
//         return 1;
//     }

//     // Redirect stdout to file
//     if (dup2(fd, STDOUT_FILENO) < 0) {
//         perror("minishell");
//         close(fd);
//         close(stdout_backup);
//         return 1;
//     }
//     close(fd);

//     // Execute the command
//     int exit_code = execute_command(cmd_node, data);

//     // Restore stdout
//     if (dup2(stdout_backup, STDOUT_FILENO) < 0) {
//         perror("minishell");
//         exit_code = 1;
//     }
//     close(stdout_backup);

//     return exit_code;
// }

// int handle_redirections(t_ast *node, t_data *data) {
//     int stdout_backup = -1;
//     t_ast *cmd_node = NULL;
//     char *filename = NULL;

//     // Find the command and redirection parts
//     t_lst *current = node->node_list;
//     while (current) {
//         t_ast *child = (t_ast *)current->content;
//         if (child && child->token) {
//             if (has_token_flag(child->token->flags, REDIRECTION_OUTPUT)) {
//                 // Get the filename from next node
//                 if (current->next) {
//                     t_ast *file_node = (t_ast *)current->next->content;
//                     if (file_node && file_node->token) {
//                         filename = file_node->token->content;
//                     }
//                 }
//             }
//             else if (has_token_flag(child->token->flags, COMMAND)) {
//                 cmd_node = child;
//             }
//         }
//         current = current->next;
//     }

//     // Set up redirection
//     if (filename) {
//         int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (fd < 0) return (perror("open"), 1);
//         stdout_backup = dup(STDOUT_FILENO);
//         dup2(fd, STDOUT_FILENO);
//         close(fd);
//     }

//     // Execute the command
//     int exit_code = 0;
//     if (cmd_node) {
//         exit_code = execute_command(cmd_node, data);
//     }

//     // Restore stdout if redirected
//     if (stdout_backup != -1) {
//         dup2(stdout_backup, STDOUT_FILENO);
//         close(stdout_backup);
//     }

//     return exit_code;
// }

t_lst *find_redirections(t_ast *node) {
    t_lst *redirs = NULL;
    t_lst *current = node->node_list;
    
    while (current) {
        t_ast *child = (t_ast *)current->content;
        if (child->token && 
            (has_token_flag(child->token->flags, REDIRECTION_OUTPUT) ||
             has_token_flag(child->token->flags, REDIRECTION_INPUT))) {
            ft_lstadd_back(&redirs, ft_lstnew(child));
        }
        current = current->next;
    }
    return redirs;
}

int setup_redirections(t_lst *redirections) {
    t_lst *current = redirections;
    while (current) {
        t_ast *redir = (t_ast *)current->content;
        if (has_token_flag(redir->token->flags, REDIRECTION_OUTPUT)) {
            t_ast *file_node = (t_ast *)redir->node_list->content;
            int fd = open(file_node->token->content, O_WRONLY|O_CREAT|O_TRUNC, 0644);
            if (fd < 0 || dup2(fd, STDOUT_FILENO) < 0) {
                perror("minishell");
                return 1;
            }
            close(fd);
        }
        // Handle other redirection types similarly
        current = current->next;
    }
    return 0;
}

int	execute_command(t_ast *node, t_data *data)
{
	char	**args;
	pid_t	pid;
	char	*cmd_path;
	int		status;

	args = build_cmd_args(node);
	t_lst *redirections = find_redirections(node);
	if (setup_redirections(redirections) != 0)
		return 1;
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
