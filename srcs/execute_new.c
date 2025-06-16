/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:12:35 by zernest           #+#    #+#             */
/*   Updated: 2025/06/16 11:45:29 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd_seqs(t_lst *cmd_seqs, t_data *data)
{
	// t_lst	*head;
	t_cmd_seq	*cmd_seq;

	if (cmd_seqs == NULL)
		return (1);
	cmd_seq = cmd_seqs->content;
	if (cmd_seq == NULL)
		return (1);
	if (DEBUG)
		printf("%p\n", cmd_seqs->content);
	if (process_heredocs(cmd_seqs) != 0)
		return (1);
	if (ft_lstsize(cmd_seqs) > 1)
		return (execute_pipeline(cmd_seqs, data));
	// head = cmd_seqs;
	if (cmd_seq == NULL)
		return (1);
	else if (ft_lstsize(cmd_seqs) == 1 && count_null_terminated_arr(cmd_seq->argv) == 0 && cmd_seq->assignment != NULL)
		return (execute_assignment(cmd_seq, data));
	else if (count_null_terminated_arr(cmd_seq->argv) >= 1)
		return (execute_command(cmd_seq, data));
	else
		return (1);
}

int	process_heredocs(t_lst *cmd_seqs)
{
	t_cmd_seq	*cmd;
	t_lst		*io_list;
	t_io		*io;
	int			pipe_fd[2];
	char		*line;

	while (cmd_seqs != 0)
	{
		cmd = cmd_seqs->content;
		io_list = cmd->io_list;
		while (io_list)
		{
			io = io_list->content;
			if (io->flag == REDIRECTION_DELIMITER)
			{
				if (pipe(pipe_fd) < 0)
					return (perror("pipe"), 1);
				while (1)
				{
					line = readline("> ");
					if (!line || ft_strncmp(line, io->content, ft_strlen(line) + 1) == 0)
					{
						free(line);
						break;
					}
					write(pipe_fd[1], line, ft_strlen(line));
					write(pipe_fd[1], "\n", 1);
					free(line);
				}
				close(pipe_fd[1]);
				io->fd = pipe_fd[0];
			}
			io_list = io_list->next;
		}
		cmd_seqs = cmd_seqs->next;
	}
	return (0);
}

int execute_pipeline(t_lst *cmd_seqs, t_data *data)
{
	int		pipe_fd[2];
	int		prev_fd = -1;
	pid_t	pid;
	int		status;
	t_cmd_seq *cmd_seq;

	while (cmd_seqs)
	{
		cmd_seq = (t_cmd_seq *)cmd_seqs->content;
		if (cmd_seqs->next)
			pipe(pipe_fd);
		if (DEBUG)
			printf("forking: %s\n", cmd_seq->argv[0]);
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (cmd_seqs->next)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], 1);
				close(pipe_fd[1]);
			}
			apply_redirections(cmd_seq->io_list);
			execve_wrapper(cmd_seq, data);
		}
		else
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			if (prev_fd != -1)
				close(prev_fd);
			if (cmd_seqs->next)
			{
				close(pipe_fd[1]);
				prev_fd = pipe_fd[0];
			}
		}
		cmd_seqs = cmd_seqs->next;
	}
	while (wait(&status) > 0);
	return (WEXITSTATUS(status));
}

void apply_redirections(t_lst *io_list)
{
	t_io *io;
	int fd;

	while (io_list)
	{
		io = (t_io *)io_list->content;
		if (io->flag == REDIRECTION_OUTPUT)
		{
			fd = open(io->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				perror("open");
			else
			{
				dup2(fd, 1);
				close(fd);
			}
		}
		else if (io->flag == REDIRECTION_APPEND)
		{
			fd = open(io->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
				perror("open");
			else
			{
				dup2(fd, 1);
				close(fd);
			}
		}
		else if (io->flag == REDIRECTION_INPUT)
		{
			fd = open(io->content, O_RDONLY);
			if (fd < 0)
				perror("open");
			else
			{
				dup2(fd, 0);
				close(fd);
			}
		}
		else if (io->flag == REDIRECTION_DELIMITER)
		{
			dup2(io->fd, 0);
			close(io->fd);
		}
		io_list = io_list->next;
	}
}

int is_builtin(char *cmd)
{
	return ( ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "history", 8) == 0
	);
}

int run_builtin(char **args, t_data *data)
{
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (builtin_echo(args));
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (builtin_cd(args + 1, data));
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (builtin_env(data->envp));
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (builtin_exit(args, data));
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (builtin_unset(args, &data->envp, &data->env_var_lst));
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (builtin_export(args, &data->envp, data));
	if (ft_strncmp(args[0], "history", 8) == 0)
		return (builtin_history(data));
	return (1);
}

void execve_wrapper(t_cmd_seq *cmd_seq, t_data *data)
{
	char **args = cmd_seq->argv;
	char *cmd_path;
	// int fd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (is_builtin(args[0]))
		exit(run_builtin(args, data));
	if (is_token_executable(args[0]))
		cmd_path = args[0];
	else
		cmd_path = find_cmd_path(args[0], data->env_var_lst);
	// fd = open(cmd_path, O_RDONLY);
	// if (fd != -1)
	// 	close(fd);
	// else if (errno == EISDIR)		errno is forbidden
	// {
	// 	printf("%s: Is a directory\n", cmd_path);
	// 	free_exit(126, data);
	// }
	if (DEBUG == 1)
		printf("cmd_path: %s\n", cmd_path);
	apply_redirections(cmd_seq->io_list);
	if (cmd_path)
		execve(cmd_path, args, data->envp);
	// Handle failure somehow use perror properly?
	if (get_env_var_value("PATH", data->env_var_lst) == NULL)
		printf("%s: No such file or directory\n", args[0]);
	else
		printf("%s: command not found\n", args[0]);
	free_exit(127, data);
}

int	execute_command(t_cmd_seq *cmd_seq, t_data *data)
{
	char	**args;
	pid_t	pid;
	int		status;

	args = cmd_seq->argv;
	if (DEBUG == 1)
	{
		for (int i = 0; args && args[i]; i++)
			printf("arg[%d] = \"%s\"\n", i, args[i]);
		printf("Executing command: %s\n", args[0]);
	}

	status = -1;
	if (!args || !args[0])
		return (1);
	if (is_builtin(args[0]) && cmd_seq->io_list == NULL)
	{
		status = run_builtin(args, data);
		free_tokens(&data->free_ptr_tokens);
		free_cmd_seqs(&data->free_ptr_cmd_seqs);
		return (status);
	}
	if (DEBUG == 1)
		printf("Last exit code: %d\n", data->last_exit_code);
	pid = fork();
	if (pid == 0)
	{
		apply_redirections(cmd_seq->io_list);
		execve_wrapper(cmd_seq, data);
	}
	else
	{	
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				write(STDOUT_FILENO, "\n", 1);
			}
		signal(SIGINT, ctrlc_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	free_tokens(&data->free_ptr_tokens);
	free_cmd_seqs(&data->free_ptr_cmd_seqs);
	return (WEXITSTATUS(status));
}

int	execute_assignment(t_cmd_seq *cmd_seq, t_data *data)
{
	t_env_var *env_var;

	env_var = split_assignment(cmd_seq->assignment);
	if (env_var == NULL || env_var->key == NULL)
		return (1);
	set_env_variable(data->env_var_lst, env_var, &data->envp);
	free_tokens(&data->free_ptr_tokens);
	free_cmd_seqs(&data->free_ptr_cmd_seqs);
	return (0);
}

// int execute_pipeline(t_ast *pipe_node, t_data *data)
// {
// 	int pipe_fd[2];
// 	pid_t pid1, pid2;
// 	int	status1;
// 	int	status2;

// 	if (!pipe_node || ft_lstsize(pipe_node->node_list) != 2)
// 		return (1);
// 	t_ast *left = (t_ast *)pipe_node->node_list->content;
// 	t_ast *right = (t_ast *)pipe_node->node_list->next->content;
// 	if (pipe(pipe_fd) < 0)
// 	{
// 		perror("pipe");
// 		return (1);
// 	}
// 	pid1 = fork();
// 	// left side
// 	if (pid1 == 0)
// 	{
// 		close(pipe_fd[0]);
// 		dup2(pipe_fd[1], 1);
// 		close(pipe_fd[1]);
// 		exit(execute_ast(left, data));
// 	}
// 	// right side
// 	pid2 = fork();
// 	if (pid2 == 0)
// 	{
// 		close(pipe_fd[1]);
// 		dup2(pipe_fd[0], 0);
// 		close(pipe_fd[0]);
// 		exit(execute_ast(right, data));
// 	}
// 	close(pipe_fd[0]);
// 	close(pipe_fd[1]);
// 	waitpid(pid1, &status1, 0);
// 	waitpid(pid2, &status2, 0);
// 	printf("Left exit: %d\n", WEXITSTATUS(status1));
// 	printf("Right exit: %d\n", WEXITSTATUS(status2));

// 	if (WIFEXITED(status2))
// 		return WEXITSTATUS(status2);
// 	else
// 		return 1;
// }

// int execute_redirection_in(t_ast *redir_node, t_data *data)
// {
// 	t_ast *cmd_node = (t_ast *)redir_node->node_list->content;
// 	t_ast *file_node = (t_ast *)redir_node->node_list->next->content;

// 	if (!redir_node || !redir_node->node_list || 
// 		ft_lstsize(redir_node->node_list) != 2)
// 	{
// 		fprintf(stderr, "minishell: syntax error near input redirection\n");
// 		return (1);
// 	}
// 	if (!file_node->token || !file_node->token->content)
// 	{
// 		fprintf(stderr, "minishell: missing input filename\n");
// 		return (1);
// 	}
// 	int fd = open(file_node->token->content, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("minishell");
// 		return (1);
// 	}
// 	int stdin_backup = dup(0);
// 	if (stdin_backup < 0)
// 	{
// 		perror("dup");
// 		close(fd);
// 		return (1);
// 	}

// 	if (dup2(fd, 0) < 0)
// 	{
// 		perror("dup2");
// 		close(fd);
// 		close(stdin_backup);
// 		return (1);
// 	}
// 	close(fd);
// 	int exit_code = execute_command(cmd_node, data);
// 	if (dup2(stdin_backup, 0) < 0)
// 	{
// 		perror("restore stdin");
// 	}
// 	close(stdin_backup);
// 	return exit_code;
// }

// int execute_redirection_out(t_ast *redir_node, t_data *data){

// 	if (!redir_node || !redir_node->node_list || 
// 		ft_lstsize(redir_node->node_list) != 2) {
// 		fprintf(stderr, "Syntax error near redirection\n");
// 		return 1;
// 	}

// 	t_ast *cmd_node = (t_ast *)redir_node->node_list->content;
// 	t_ast *file_node = (t_ast *)redir_node->node_list->next->content;
// 	int fd = open(file_node->token->content, 
// 				O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd < 0) {
// 		perror("minishell");
// 		return 1;
// 	}

// 	int stdout_backup = dup(1);
// 	if (stdout_backup < 0 || dup2(fd, 1) < 0) {
// 		perror("minishell");
// 		close(fd);
// 		return 1;
// 	}
// 	close(fd);
// 	int exit_code = execute_command(cmd_node, data);

// 	if (dup2(stdout_backup, 1) < 0) {
// 		perror("minishell");
// 		exit_code = 1;
// 	}
// 	close(stdout_backup);

// 	return exit_code;
// }