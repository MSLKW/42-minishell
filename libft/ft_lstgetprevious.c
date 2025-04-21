/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetprevious.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:34:00 by maxliew           #+#    #+#             */
/*   Updated: 2025/04/14 21:46:36 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst	*ft_lstgetprevious(t_lst **lst, t_lst *current_lst)
{
	int	current_lst_index;

	current_lst_index = ft_lstgetindex(lst, current_lst);
	if (current_lst_index == 0)
		return (NULL);
	return (ft_lstindex(lst, current_lst_index - 1));
}
