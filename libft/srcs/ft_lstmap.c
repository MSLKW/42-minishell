/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yilim <yilim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:53:32 by yilim             #+#    #+#             */
/*   Updated: 2024/03/11 00:08:36 by yilim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_cur;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	new_cur = new;
	while (lst->next)
	{
		new_cur->next = ft_lstnew(f(lst->next->content));
		if (!new_cur->next)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		new_cur = new_cur->next;
		lst = lst->next;
	}
	return (new);
}
