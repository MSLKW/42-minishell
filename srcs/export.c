/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:45:01 by zernest           #+#    #+#             */
/*   Updated: 2025/04/28 15:52:22 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_export(char *arg, char ***envp)
{
	int	i;
	char **new_env;

	i = 0;
	if (!arg)
	{
		//THIS PART TO PRINT ENVIRONMENT WIP
		return(0);
	}
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (1);

	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;

	free(*envp);
	*env = new_env;

	return (0);
}