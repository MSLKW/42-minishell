/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetindex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 08:54:41 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/12 22:42:10 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstgetindex(t_lst **lst, t_lst *lst_to_find)
{
	t_lst	*head;
	int		index;

	if (lst == NULL || *lst == NULL || lst_to_find == NULL)
		return (-1);
	head = *lst;
	index = 0;
	while (head != NULL)
	{
		if (head == lst_to_find)
			return (index);
		index++;
		head = head->next;
	}
	return (-1);
}
