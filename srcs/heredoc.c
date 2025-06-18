/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:29:55 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 14:30:06 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(t_io *io, t_data *data)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) < 0)
		return (perror("pipe"), 1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strncmp(line, io->content, ft_strlen(line) + 1) == 0)
		{
			free(line);
			break ;
		}
		line = variable_expansion(line, data, NULL);
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	io->fd = pipe_fd[0];
	return (0);
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
				if (handle_heredoc(io, data) != 0)
					return (1);
			}
			io_list = io_list->next;
		}
		cmd_seqs = cmd_seqs->next;
	}
	return (0);
}
