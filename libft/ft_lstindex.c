/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 06:30:29 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/12 22:42:10 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstindex(t_lst **lst, int to_index)
{
	t_lst	*head;
	int		index;

	if (to_index < 0 || lst == NULL)
		return (NULL);
	head = *lst;
	index = 0;
	while (index < to_index && head != NULL)
	{
		index++;
		head = head->next;
	}
	return (head);
}
