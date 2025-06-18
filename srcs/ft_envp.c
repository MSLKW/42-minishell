/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 23:36:16 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/17 23:58:41 by maxliew          ###   ########.fr       */
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

int	ft_addenv(char *arg, char ***envp)
{
	char	**envp_copy;
	int		i;

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
	free_str_arr(*envp);
	*envp = envp_copy;
	return (0);
}

int	ft_setenv(char *key, char *value, char ***envp)
{
	int	env_index;

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
	int			env_index;
	t_env_var	*env_var;

	env_index = find_env_index(envp, key);
	if (env_index == -1)
		return (NULL);
	env_var = split_assignment(envp[env_index]);
	if (env_var == NULL)
		return (NULL);
	return (env_var->value);
}
