/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:40:30 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 02:15:41 by maxliew          ###   ########.fr       */
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

static t_lst	*split_variable_list(const char *arg)
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

static t_bool	expand_env_var(t_lst *head, char *arg, t_data *data)
{
	t_env_var	*var;

	var = get_env_variable(arg + 1, data->env_var_lst);
	if (var == NULL)
		head->content = ft_strdup("");
	free(arg);
	if (var != NULL && var->value != NULL)
	{
		head->content = ft_strdup(var->value);
		return (TRUE);
	}
	else if (var != NULL && var->value == NULL)
		head->content = ft_strdup("");
	return (FALSE);
}

/*
	Iterates the list and expands any variable inside
*/
static t_bool	expand_variable(t_lst *head, char *arg, t_data *data)
{
	t_bool		is_expanded;

	arg = head->content;
	is_expanded = FALSE;
	if (ft_strlen(arg) >= 2 && arg[0] == '$')
	{
		if (arg[1] == '?')
		{
			head->content = ft_itoa(data->last_exit_code);
			free(arg);
			return (TRUE);
		}
		is_expanded = expand_env_var(head, arg, data);
	}
	return (is_expanded);
}

static t_bool	domain_variable_expansion(t_lst	*split_arg_list, t_data *data)
{
	t_lst		*head;
	char		*arg;
	t_bool		is_expanded;

	is_expanded = FALSE;
	head = split_arg_list;
	while (head != NULL)
	{
		arg = head->content;
		if (expand_variable(head, arg, data) == TRUE)
			is_expanded = TRUE;
		head = head->next;
	}
	return (is_expanded);
}

static char	*rejoining_strs(t_lst *split_arg)
{
	t_lst	*head;
	char	*base_str;
	char	*temp;

	base_str = ft_calloc(1, (sizeof(char)));
	if (base_str == NULL)
		return (NULL);
	base_str[0] = '\0';
	head = split_arg;
	while (head != NULL)
	{
		if (head->content != NULL)
		{
			temp = base_str;
			base_str = ft_strjoin(temp, head->content);
			free(temp);
		}
		head = head->next;
	}
	return (base_str);
}

/*
	Returns argument with variables expanded in it
	status returns TRUE if any variable is successfully expanded with content
*/
char	*variable_expansion(const char *arg, t_data *data, t_bool *status)
{
	t_lst	*split_arg;
	char	*result;
	t_bool	is_expanded;

	if (arg == NULL)
		return (NULL);
	split_arg = split_variable_list(arg);
	is_expanded = domain_variable_expansion(split_arg, data);
	if (status != NULL)
		*status = is_expanded;
	result = rejoining_strs(split_arg);
	ft_lstclear(&split_arg, free);
	return (result);
}
