/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:26:59 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 14:51:03 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_redirections(t_lst *io_list)
{
	t_io	*io;

	while (io_list)
	{
		io = (t_io *)io_list->content;
		if (io->flag == REDIRECTION_OUTPUT)
			handle_output(io->content);
		else if (io->flag == REDIRECTION_APPEND)
			handle_append(io->content);
		else if (io->flag == REDIRECTION_INPUT)
			handle_input(io->content);
		else if (io->flag == REDIRECTION_DELIMITER)
			handle_heredoc_redirection(io->fd);
		io_list = io_list->next;
	}
}

void	handle_output(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("open");
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror("open");
	else
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

void	handle_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("open");
	else
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	handle_heredoc_redirection(int fd)
{
	dup2(fd, STDIN_FILENO);
	close(fd);
}
