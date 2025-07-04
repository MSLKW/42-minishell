/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:45:01 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 17:07:51 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_export_identifer(char *key, char *value)
{
	char	*part1;
	char	*part2;

	if (key == NULL || value == NULL)
		return (NULL);
	part1 = ft_strjoin(key, "=");
	part2 = ft_strjoin(part1, value);
	free(part1);
	return (part2);
}

int	ft_exportcheck(t_env_var *var, char ***envp)
{
	if (var == NULL)
		return (1);
	if (var->value != NULL && var->is_export == TRUE)
	{
		ft_setenv(var->key, var->value, envp);
		return (0);
	}
	return (1);
}

static int	unregular_export(char *arg, char ***envp, t_lst *env_var_lst)
{
	t_env_var	*var;

	var = get_env_variable(arg, env_var_lst);
	if (var != NULL)
	{
		var->is_export = TRUE;
		ft_exportcheck(var, envp);
	}
	else if (var == NULL)
	{
		var = init_env_variable(arg, NULL);
		if (var == NULL)
		{
			ft_put_error(arg, "not a valid identifier");
			return (1);
		}
		var = set_env_variable(env_var_lst, var, envp);
		var->is_export = TRUE;
	}
	return (0);
}

int	process_args(char **args, char ***envp, t_lst *env_var_lst)
{
	int			i;
	t_env_var	*var;

	i = 1;
	while (args[i] != NULL)
	{
		var = split_assignment(args[i]);
		if (var != NULL)
		{
			var->is_export = TRUE;
			var = set_env_variable(env_var_lst, var, envp);
		}
		else
		{
			if (unregular_export(args[i], envp, env_var_lst) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_export(char **args, char ***envp, t_data *data)
{
	if (args == NULL || envp == NULL || data == NULL)
		return (1);
	if (count_null_terminated_arr(args) == 1)
		display_export(data->env_var_lst);
	else
	{
		if (process_args(args, envp, data->env_var_lst) == 1)
			return (1);
	}
	return (0);
}
