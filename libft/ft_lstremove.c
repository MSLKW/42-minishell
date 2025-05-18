/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:13:42 by maxliew           #+#    #+#             */
/*   Updated: 2024/07/18 10:23:46 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstremove(t_lst *lst_del, t_lst *prev_lst, void (*del)(void *))
{
	t_lst	*lst_del_next;

	if (lst_del == NULL)
		return (NULL);
	lst_del_next = lst_del->next;
	ft_lstdelone(lst_del, del);
	if (prev_lst != NULL)
	{
		prev_lst->next = lst_del_next;
		return (prev_lst);
	}
	return (lst_del_next);
}