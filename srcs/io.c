/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:40:28 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 00:06:11 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_io	*init_io(char *content, t_flag flag)
{
	t_io	*io;

	io = ft_calloc(1, sizeof(t_io));
	if (!io)
		return (NULL);
	io->content = content;
	io->flag = flag;
	io->fd = -1;
	return (io);
}

t_flag	get_redirection_flag(t_flag *flags)
{
	if (flags == NULL)
		return (NO_FLAG);
	else if (has_token_flag(flags, REDIRECTION_INPUT))
		return (REDIRECTION_INPUT);
	else if (has_token_flag(flags, REDIRECTION_OUTPUT))
		return (REDIRECTION_OUTPUT);
	else if (has_token_flag(flags, REDIRECTION_APPEND))
		return (REDIRECTION_APPEND);
	else if (has_token_flag(flags, REDIRECTION_DELIMITER))
		return (REDIRECTION_DELIMITER);
	return (NO_FLAG);
}

t_lst	*get_io_list(t_lst *token_list, int *status)
{
	t_lst	*head;
	t_token	*token;
	t_flag	io_flag;
	t_lst	*io_list;

	io_list = NULL;
	io_flag = NO_FLAG;
	head = token_list;
	while (head != NULL)
	{
		token = head->content;
		if (has_token_flag(token->flags, REDIRECTION))
			io_flag = get_redirection_flag(token->flags);
		else if (has_token_flag(token->flags, REDIRECTION_ARGUMENT))
		{
			ft_lstadd_back(&io_list, ft_lstnew(init_io(ft_strdup(token->content), io_flag)));
			io_flag = NO_FLAG;
		}
		head = head->next;
	}
	if (io_flag != NO_FLAG)
	{
		if (io_list != NULL)
			ft_lstclear(&io_list, free_io);
		*status = 1;
	}
	return (io_list);
}
