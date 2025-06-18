/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:28:30 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 21:51:32 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process(int *prev_fd, int *pipe_fd, t_bool has_next)
{
	// signal(SIGINT, SIG_IGN);
	// signal(SIGQUIT, SIG_IGN);
	if (*prev_fd != -1)
		close(*prev_fd);
	if (has_next)
	{
		close(pipe_fd[1]);
		*prev_fd = pipe_fd[0];
	}
}

void	child_process(t_lst *cmd_seqs, t_data *data, int prev_fd, int *pipe_fd)
{
	t_cmd_seq	*cmd_seq;
	t_bool		has_next;

	cmd_seq = cmd_seqs->content;
	has_next = (cmd_seqs->next != NULL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, 0);
		close(prev_fd);
	}
	if (has_next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
	}
	apply_redirections(cmd_seq->io_list);
	execve_wrapper(cmd_seq, data);
}

int	execute_pipeline(t_lst *cmd_seqs, t_data *data)
{
	int			pipe_fd[2];
	int			prev_fd;
	pid_t		pid;
	int			status;

	prev_fd = -1;
	while (cmd_seqs)
	{
		if (cmd_seqs->next)
			pipe(pipe_fd);
		pid = fork();
		if (pid == 0)
			child_process(cmd_seqs, data,
				prev_fd, pipe_fd);
		else
			parent_process(&prev_fd, pipe_fd, cmd_seqs->next != NULL);
		cmd_seqs = cmd_seqs->next;
	}
	while (wait(&status) > 0)
		;
	// signal(SIGINT, ctrlc_handler);
	return (WEXITSTATUS(status));
}
