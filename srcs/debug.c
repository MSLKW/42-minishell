/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:48:08 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/12 22:42:10 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display(t_lst *list)
{
	t_lst	*head;

	head = list;
	while (head != NULL)
	{
		ft_printf("%s\n", head->content);
		head = head->next;
	}
}