/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:40:30 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/30 23:30:34 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle setting var through var_name=value with execution
// handle unsetting env and var_name

// if variable is in env, env variable gets changed.

// if var is exported, then set through var=value
// var is seen on env.

// export will take from variable.c and set if there is any to be set, but will display any variable with value from variable.c

static t_lst	*split_variable_list(const char *arg)
{
	t_lst	*arg_list;
	int		start_index;
	int		end_index;

	if (arg == NULL)
		return (NULL);
	arg_list = NULL;
	start_index = 0;
	end_index = 0;
	while (arg[start_index + end_index] != '\0')
	{
		if (arg[start_index + end_index] == '$')
		{
			ft_lstadd_back(&arg_list, ft_lstnew(ft_substr(arg, start_index, end_index)));
			start_index += end_index;
			end_index = 1;
			if (ft_isalpha(arg[start_index + end_index]) == TRUE || arg[start_index + end_index] == '?')
			{
				while (arg[start_index + end_index] != '\0' && (ft_isalnum(arg[start_index + end_index]) == TRUE || arg[start_index + end_index] == '_' || arg[start_index + end_index] == '?'))
				{
					end_index++;
				}
				ft_lstadd_back(&arg_list, ft_lstnew(ft_substr(arg, start_index, end_index)));
				start_index += end_index;
				end_index = 0;
			}
			else
			{
				ft_lstadd_back(&arg_list, ft_lstnew(ft_substr(arg, start_index, end_index)));
				start_index += end_index;
				end_index = 1;
			}
		}
		else
			end_index++;
	}
	ft_lstadd_back(&arg_list, ft_lstnew(ft_substr(arg, start_index, end_index)));
	return (arg_list);
}

// static char	*clear_new_lines(const char *str)
// {
// 	int		i;
// 	char	*

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] != '\n')
// 			i++;
// 	}
// }
/*
	Iterates the list and expands any variable inside
*/
static void	domain_variable_expansion(t_lst	*split_arg_list, t_data *data)
{
	t_lst		*head;
	char		*arg;
	t_env_var	*var;

	head = split_arg_list;
	while (head != NULL)
	{
		arg = head->content;
		if (ft_strlen(arg) >= 2 && arg[0] == '$')
		{
			if (arg[1] == '?')
				head->content = ft_itoa(data->last_exit_code);
			else
			{
				var = get_env_variable(arg + 1, data->env_var_lst);
				if (var == NULL)
					head->content = ft_strdup("");
				free(arg);
				if (var != NULL && var->value != NULL)
					head->content = ft_strdup(var->value);
				else if (var != NULL && var->value == NULL)
					head->content = ft_strdup("");
			}
		}
		head = head->next;
	}
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
*/
char	*variable_expansion(const char *arg, t_data *data)
{
	t_lst	*split_arg;
	char	*result;

	split_arg = split_variable_list(arg);
	// ft_lststrdisplay(split_arg);
	domain_variable_expansion(split_arg, data);
	// ft_lststrdisplay(split_arg);
	result = rejoining_strs(split_arg);
	ft_lstclear(&split_arg, free);
	return (result);
}
