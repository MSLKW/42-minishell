/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_display.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:12:08 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 15:12:15 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	display_export(t_lst *env_var_lst)
{
	t_lst		*head;
	t_env_var	*env_var;

	if (env_var_lst == NULL)
		return (1);
	head = env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (env_var != NULL && env_var->key != NULL \
&& env_var->is_export == TRUE)
		{
			if (env_var->value == NULL)
				printf("declare -x %s\n", env_var->key);
			else
				printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
		}
		head = head->next;
	}
	return (0);
}
