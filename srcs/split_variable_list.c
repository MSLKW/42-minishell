/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_variable_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:09:52 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 15:10:15 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dollar_sign_split(const char *arg, int *s, int *e, t_lst **arg_lst)
{
	ft_lstadd_back(arg_lst, ft_lstnew(ft_substr(arg, *s, *e)));
	*s += *e;
	*e = 1;
	if (ft_isalpha(arg[*s + *e]) == TRUE || arg[*s + *e] == '?')
	{
		if (arg[*s + *e] == '?')
			(*e)++;
		else
		{
			while (arg[*s + *e] != '\0' && \
(ft_isalnum(arg[*s + *e]) == TRUE || arg[*s + *e] == '_'))
				(*e)++;
		}
		ft_lstadd_back(arg_lst, ft_lstnew(ft_substr(arg, *s, *e)));
		*s += *e;
		*e = 0;
	}
	else
	{
		ft_lstadd_back(arg_lst, ft_lstnew(ft_substr(arg, *s, *e)));
		*s += *e;
		*e = 1;
	}
}

t_lst	*split_variable_list(const char *arg)
{
	t_lst	*arg_list;
	int		s;
	int		e;

	if (arg == NULL)
		return (NULL);
	arg_list = NULL;
	s = 0;
	e = 0;
	while (arg[s + e] != '\0')
	{
		if (arg[s + e] == '$')
			dollar_sign_split(arg, &s, &e, &arg_list);
		else
			e++;
	}
	ft_lstadd_back(&arg_list, ft_lstnew(ft_substr(arg, s, e)));
	return (arg_list);
}
