/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:13:16 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/12 22:42:10 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_lst **lst, void (*del)(void *))
{
	t_lst	*next_list;
	t_lst	*temp;

	if (lst == NULL || del == NULL)
		return ;
	next_list = *lst;
	while (next_list->next != NULL)
	{
		temp = next_list;
		next_list = next_list->next;
		ft_lstdelone(temp, del);
	}
	ft_lstdelone(next_list, del);
	*lst = NULL;
}
// do i need temp to delete or can i just use next_list?