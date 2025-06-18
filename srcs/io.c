/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 00:40:28 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 14:00:59 by maxliew          ###   ########.fr       */
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

static void	io_lst_logic(t_token *token, t_flag *io_flag, t_lst **io_list)
{
	if (has_token_flag(token->flags, REDIRECTION))
		*io_flag = get_redirection_flag(token->flags);
	else if (has_token_flag(token->flags, REDIRECTION_ARGUMENT))
	{
		ft_lstadd_back(io_list, \
ft_lstnew(init_io(ft_strdup(token->content), *io_flag)));
		*io_flag = NO_FLAG;
	}
}

t_lst	*get_io_list(t_lst *token_lst, int *status)
{
	t_token	*token;
	t_flag	io_flag;
	t_lst	*io_list;

	io_list = NULL;
	io_flag = NO_FLAG;
	while (token_lst != NULL)
	{
		token = token_lst->content;
		io_lst_logic(token, &io_flag, &io_list);
		token_lst = token_lst->next;
	}
	if (io_flag != NO_FLAG)
	{
		if (io_list != NULL)
			ft_lstclear(&io_list, free_io);
		*status = 1;
	}
	return (io_list);
}
