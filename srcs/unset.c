/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:09:09 by zernest           #+#    #+#             */
/*   Updated: 2025/05/06 16:13:50 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_key_match(const char *env_entry, const char *key)
{
	size_t key_len = strlen(key);
	return (strncmp(env_entry, key, key_len) == 0 && env_entry[key_len] == '=');
}

int	builtin_unset_env(char *key, char ***envp_copy)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
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
