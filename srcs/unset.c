/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:09:09 by zernest           #+#    #+#             */
/*   Updated: 2025/06/14 10:59:09 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_key_match(const char *env_entry, const char *key)
{
	size_t key_len;
	
	key_len = strlen(key);
	return (strncmp(env_entry, key, key_len) == 0 && env_entry[key_len] == '=');
}

int	unset_env(char *key, char ***envp_copy, t_lst **env_var_lst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (key == NULL || envp_copy == NULL || env_var_lst == NULL)
		return (1);
	unset_env_variable(key, env_var_lst);
	while ((*envp_copy)[i])
	{
		if (env_key_match((*envp_copy)[i], key))
		{
			free((*envp_copy)[i]);
			j = i;
			while ((*envp_copy)[j])
			{
				(*envp_copy)[j] = (*envp_copy)[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_unset(char **args, char ***envp_copy, t_lst **env_var_lst)
{
	int		i;

	i = 1;
	if (args == NULL || envp_copy == NULL || env_var_lst == NULL)
		return (1);
	while (args[i] != NULL)
	{
		unset_env(args[i], envp_copy, env_var_lst);
		i++;
	}
	return (0);
}
