/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetprevious.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:34:00 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/12 22:47:13 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstgetprevious(t_lst **lst, t_lst *lst_to_find)
{
	int	lst_to_find_index;

	lst_to_find_index = ft_lstgetindex(lst, lst_to_find);
	if (lst_to_find_index == 0)
		return (NULL);
	return (ft_lstindex(lst, lst_to_find_index - 1));
}
