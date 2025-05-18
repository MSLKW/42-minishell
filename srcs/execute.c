/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:42:19 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/13 16:44:52 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Find where the command path is in the many bins dictated by PATH in envp
*/
char	*find_cmd_path(char *cmd, char *envp[])
{
	int		index;
	char	**envp_paths;
	char	*dir_path;
	char	*full_path;

	index = 0;
	while (ft_strnstr(envp[index], "PATH", 4) == NULL)
		index++;
	envp_paths = ft_split(envp[index] + 5, ':');
	index = 0;
	while (envp_paths[index] != NULL)
	{
		dir_path = ft_strjoin(envp_paths[index], "/");
		full_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		index++;
	}
	index = -1;
	while (envp_paths[++index] != NULL)
		free(envp_paths[index]);
	free(envp_paths);
	return (NULL);
}

// void	execute_cmd(t_ast *cmd_ast, t_data *data)
// {
// 	char	*cmd_path;
// 	t_token	*cmd_token;

// 	cmd_token = cmd_ast->token;
// 	if (cmd_token->secondary_type != COMMAND)
// 		return ;
// 	if (is_token_builtin(cmd_token->content) == TRUE)
// 	{
// 		execute_builtin(cmd_token->content, get_args_from_ast(cmd_ast->node_list), data);
// 	}
// 	else
// 	{
// 		cmd_path = find_cmd_path(cmd_token->content, data->envp);
// 		if (cmd_path == NULL)
// 		{
// 			printf("Error: No command found\n");
// 			return ;
// 		}
// 		execve(cmd_path, get_args_from_ast(cmd_ast->node_list), data->envp);
// 	}
// }

// void	execute_builtin(char *cmd_name, char **args, t_data *data)
// {
// 	if (is_token_builtin(cmd_name) == FALSE)
// 		return ;
// 	if (ft_strncmp(cmd_name, "echo", ft_strlen(cmd_name)) == 0)
// 	{
// 		builtin_echo(args);
// 	}
// 	else if(ft_strncmp(cmd_name, "cd", ft_strlen(cmd_name)) == 0)
// 	{
// 		builtin_cd(args);
// 	}
// 	else if (ft_strncmp(cmd_name, "pwd", ft_strlen(cmd_name)) == 0)
// 	{
// 		builtin_pwd();
// 	}
// 	else if (ft_strncmp(cmd_name, "export", ft_strlen(cmd_name)) == 0)
// 	{
// 		// builtin_export(args[0], data->envp);
// 	}
// 	else if (ft_strncmp(cmd_name, "unset", ft_strlen(cmd_name)) == 0)
// 	{
// 		// builtin_unset_env(args[0], &data->envp);
// 	}
// 	else if (ft_strncmp(cmd_name, "env", ft_strlen(cmd_name)) == 0)
// 	{
// 		builtin_env(data->envp);
// 	}
// 	else if (ft_strncmp(cmd_name, "exit", ft_strlen(cmd_name)) == 0)
// 	{
// 		builtin_exit(args);
// 	}
// }

// char	**get_args_from_ast(t_lst *node_list)
// {
// 	t_lst	*head;
// 	t_ast	*ast;
// 	char	**args;
// 	int		index;

// 	if (node_list == NULL)
// 		return (NULL);
// 	args = ft_calloc(ft_lstsize(node_list), sizeof(char *));
// 	head = node_list;
// 	index = 0;
// 	while (head != NULL)
// 	{
// 		ast = head->content;
// 		if (ast->token->secondary_type == ARGUMENT)
// 		{
// 			args[index] = ast->token->content;
// 		}
// 		index++;
// 		head = head->next;
// 	}
// 	return (args);
// }
