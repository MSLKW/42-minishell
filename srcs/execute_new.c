/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:12:35 by zernest           #+#    #+#             */
/*   Updated: 2025/05/08 18:07:26 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_ast *ast, t_data * data)
{
	if (!ast)
		return (1);
	return (execute_command(ast, data));
}

char	**build_cmd_args(t_ast *node)
{
	int		count;
	t_lst	*cur;
	t_token	*tok;
	char	**args;
	int		i;

	count = 0;
	cur = node->node_list;
	while (cur)
	{
		tok = (t_token *)cur->content;
		if (tok->secondary_type == COMMAND || tok->secondary_type == ARGUMENT)
			count++;
		cur = cur->next;
	}
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	cur = node->node_list;
	i = 0;
	while (cur)
	{
		tok = (t_token *)cur->content;
		if (tok->secondary_type == COMMAND || tok->secondary_type == ARGUMENT)
			args[i++] = tok->content;
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
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd());
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args + 1));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(data->envp));
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset_env(args[1], &data->envp));
	pid = fork();
	if (pid == 0)
	{
		cmd_path = find_cmd_path(args[0], data->envp);
		if (!cmd_path)
		{
			ft_printf("command not found: %s\n", args[0]);
			exit (127);
		}
		execve(cmd_path, args, data->envp);
		perror("execve");
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}
