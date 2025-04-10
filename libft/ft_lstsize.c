/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:01:50 by maxliew           #+#    #+#             */
/*   Updated: 2024/03/08 20:11:47 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*next_list;
	int		count;

	if (lst == NULL)
		return (0);
	next_list = lst;
	count = 1;
	while (next_list->next != NULL)
	{
		next_list = next_list->next;
		count++;
	}
	return (count);
}
