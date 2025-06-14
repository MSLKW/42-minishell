/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:45:01 by zernest           #+#    #+#             */
/*   Updated: 2025/06/14 14:20:57 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_index(char **envp, const char *key)
{
	int			i;
	t_env_var	*env_var;
	
	if (key == NULL || envp == NULL)
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		env_var = split_assignment(envp[i]);
		if (env_var != NULL)
		{
			if (ft_strncmp(env_var->key, key, \
				ft_strlen(env_var->key) + 1) == 0)
			{
				free_env_var(env_var);
				return (i);
			}
			free_env_var(env_var);
		}
		i++;
	}
	return (-1);
}

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

int	ft_addenv(char *arg, char ***envp)
{
	char	**envp_copy;
	int 	i;

	if (envp == NULL || *envp == NULL)
		return (1);
	envp_copy = get_envp_copy(*envp, 1);
	if (envp_copy == NULL)
		return (1);
	i = 0;
	while (envp_copy[i] != NULL)
	{
		i++;
	}
	envp_copy[i] = arg;
	// envp_copy[i + 1] = NULL;
	free_envp(*envp);
	*envp = envp_copy;
	return (0);
}

int	ft_setenv(char *key, char *value, char ***envp)
{
	int env_index;
	
	env_index = find_env_index(*envp, key);
	if (env_index == -1)
	{
		ft_addenv(join_export_identifer(key, value), envp);
		return (0);
	}
	free((*envp)[env_index]);
	(*envp)[env_index] = join_export_identifer(key, value);
	return (0);
}

char	*ft_getenv(char *key, char **envp)
{
	int 		env_index;
	t_env_var	*env_var;
	
	env_index = find_env_index(envp, key);
	if (env_index == -1)
		return (NULL);
	env_var = split_assignment(envp[env_index]);
	if (env_var == NULL)
		return (NULL);
	return (env_var->value);
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

int	process_args(char **args, char ***envp, t_lst *env_var_lst)
{
	int			i;
	t_env_var	*var;

	i = 1;
	while (args[i] != NULL)
	{
		// "export var=value"
		var = split_assignment(args[i]);
		if (var != NULL)
		{
			var->is_export = TRUE;
			var = set_env_variable(env_var_lst, var, envp);
		}
		else
		{
			// "var=5, export var"
			var = get_env_variable(args[i], env_var_lst);
			if (var != NULL)
			{
				var->is_export = TRUE;
				ft_exportcheck(var, envp);
			}
			else if (var == NULL)
			{
				// "export var, var=5"
				var = init_env_variable(args[i], NULL);
				if (var == NULL)
				{
					printf("\'%s\' is not a valid identifier\n", args[i]);
					break ;
				}
				var = set_env_variable(env_var_lst, var, envp);
				var->is_export = TRUE;
			}
		}
		i++;
	}
	return (0);
}

static int display_export(t_lst *env_var_lst)
{
	t_lst		*head;
	t_env_var	*env_var;

	if (env_var_lst == NULL)
		return (1);
	head = env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (env_var != NULL && env_var->key != NULL && env_var->is_export == TRUE)
		{
			if (env_var->value == NULL || ft_strlen(env_var->value) == 0)
				printf("declare -x %s\n", env_var->key);
			else
				printf("declare -x %s=\"%s\"\n", env_var->key, env_var->value);
		}
		head = head->next;
	}
	return (0);
}

int	builtin_export(char **args, char ***envp, t_data *data)
{
	// validate args to have only 1 argument
	if (args == NULL || envp == NULL || data == NULL)
		return (1);
	if (count_null_terminated_arr(args) == 1)
		display_export(data->env_var_lst);
	else
		process_args(args, envp, data->env_var_lst);
	return (0);
}
