/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:48:08 by maxliew           #+#    #+#             */
/*   Updated: 2025/02/21 13:50:22 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display(t_list *list)
{
	t_list	*head;

	head = list;
	while (head != NULL)
	{
		ft_printf("%s\n", head->content);
		head = head->next;
	}
}