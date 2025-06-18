/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:29:55 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 23:27:19 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	handle_heredoc(t_io *io, t_data *data)
// {
// 	int		pipe_fd[2];
// 	char	*line;
// 	pid_t	pid;

// 	signal(SIGINT, heredoc_sigint_handler);
// 	// g_sigint_received = 0;
// 	if (pipe(pipe_fd) < 0)
// 		return (perror("pipe"), 1);
// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		// if (g_sigint_received == 1)
// 		// {
// 		// 	free(line);
// 		// 	close(pipe_fd[0]);
// 		// 	close(pipe_fd[1]);
// 		// 	data->last_exit_code = 130;
// 		// 	printf("test\n");
// 		// 	// Restore signal handler
// 		// 	return (1);
// 		// }
// 		printf("test %s, %s\n",line, io->content);
// 		if (!line || ft_strncmp(line, io->content, ft_strlen(line) - 1) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		line = variable_expansion(line, data, NULL);
// 		write(pipe_fd[1], line, ft_strlen(line));
// 		write(pipe_fd[1], "\n", 1);
// 		free(line);
// 	}
// 	close(pipe_fd[1]);
// 	io->fd = pipe_fd[0];
// 	return (0);
// }

int	handle_heredoc(t_io *io, t_data *data)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);

		close(pipe_fd[0]);
		while (1)
		{

			char *line = get_next_line(0);
			if (!line)
				exit(0);
			if (ft_strncmp(line, io->content, ft_strlen(io->content)) == 0)
			{
				free(line);
				break ;
			}
			line = variable_expansion(line, data, NULL);
			write(pipe_fd[1], line, ft_strlen(line));
			// write(pipe_fd[1], "\n", 1);
			free(line);
		}
		close(pipe_fd[1]);
		free_exit(0, data);
		return (0);
	}
	else
	{
		// Parent
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipe_fd[0]);
			return (130);
		}
		io->fd = pipe_fd[0];
		return (0);
	}
}

int	process_heredocs(t_lst *cmd_seqs, t_data *data)
{
	t_cmd_seq	*cmd;
	t_lst		*io_list;
	t_io		*io;

	// signal(SIGINT, SIG_IGN);
	while (cmd_seqs)
	{
		cmd = cmd_seqs->content;
		io_list = cmd->io_list;
		while (io_list)
		{
			io = io_list->content;
			if (io->flag == REDIRECTION_DELIMITER)
			{
				if (handle_heredoc(io, data) == 130)
				{
					data->last_exit_code = 130;
					// signal(SIGINT, ctrlc_handler);
					// printf("return 1\n");
					return (1);
				}
			}
			io_list = io_list->next;
		}
		cmd_seqs = cmd_seqs->next;
	}
	// signal(SIGINT, ctrlc_handler);
	// printf("return 0\n");
	return (0);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(1, "\n", 3);
	printf("signal recieved");
}
