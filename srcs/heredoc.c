/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:29:55 by zernest           #+#    #+#             */
/*   Updated: 2025/06/19 17:53:24 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
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
		char *line = get_next_line(0);

		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipe_fd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (!line)
				exit(0);
			if (ft_strncmp(line, io->content, ft_strlen(io->content)) == 0)
			{
				free(line);
				break ;
			}
			line = variable_expansion(line, data, NULL);
			write(pipe_fd[1], line, ft_strlen(line));
			free(line);
		}
		close(pipe_fd[1]);
		free_exit(0, data);
		return (0);
	}
	else
	{
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
*/

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
		handle_heredoc_child(io, data, pipe_fd);
	else
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		{
			close(pipe_fd[0]);
			return (130);
		}
		io->fd = pipe_fd[0];
	}
	return (0);
}

void	handle_heredoc_child(t_io *io, t_data *data, int pipe_fd[2])
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(pipe_fd[0]);
	while (1)
	{
		line = get_next_line(0);
		if (!line)
			exit(0);
		if (ft_strncmp(line, io->content, ft_strlen(io->content)) == 0)
		{
			free(line);
			break ;
		}
		line = variable_expansion(line, data, NULL);
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
	}
	close(pipe_fd[1]);
	free_exit(0, data);
}

int	process_heredocs(t_lst *cmd_seqs, t_data *data)
{
	t_cmd_seq	*cmd;
	t_lst		*io_list;
	t_io		*io;

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
					return (1);
				}
			}
			io_list = io_list->next;
		}
		cmd_seqs = cmd_seqs->next;
	}
	return (0);
}

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_sigint_received = 1;
	write(1, "\n", 3);
	printf("signal recieved");
}
