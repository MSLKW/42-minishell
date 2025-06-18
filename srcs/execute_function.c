/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:42:41 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 19:20:27 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_cmd_seq *cmd_seq, t_data *data)
{
	char	**args;
	pid_t	pid;
	int		status;

	args = cmd_seq->argv;
	status = -1;
	if (!args || !args[0])
		return (1);
	if (is_builtin(args[0]) && cmd_seq->io_list == NULL)
	{
		status = run_builtin(args, data);
		return (status);
	}
	pid = fork();
	if (pid == 0)
	{
		apply_redirections(cmd_seq->io_list);
		execve_wrapper(cmd_seq, data);
	}
	else
		exec_handle_parent(pid, &status);
	return (WEXITSTATUS(status));
}

void	exec_handle_parent(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, status, 0);
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, ctrlc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	execve_wrapper(t_cmd_seq *cmd_seq, t_data *data)
{
	char	**args;
	char	*cmd_path;
	int		error_code_flag;

	args = cmd_seq->argv;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(args[0]))
		free_exit(run_builtin(args, data), data);
	error_code_flag = is_token_executable(args[0]);
	if (error_code_flag && error_code_flag != 3)
		cmd_path = args[0];
	else
		cmd_path = find_cmd_path(args[0], data->env_var_lst);
	apply_redirections(cmd_seq->io_list);
	if (cmd_path)
	{
		execve(cmd_path, args, data->envp);
		free(cmd_path);
	}
	print_execve_error(args[0], error_code_flag, data);
	free_exit(127, data);
}

void	print_execve_error(char *cmd, int flag, t_data *data)
{
	if (get_env_var_value("PATH", data->env_var_lst) == NULL)
		ft_put_error(cmd, "No such file or directory");
	else if (flag != 3)
		ft_put_error(cmd, "command not found");
	else
		ft_put_error(cmd, "Is a directory");
	free_exit(127, data);
}
