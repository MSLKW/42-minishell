/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:01:48 by zernest           #+#    #+#             */
/*   Updated: 2025/05/07 23:02:51 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **path)
{
	if (!path[0])
	{
		printf("cd: missing argument\n");
		return (1);
	}
	if (chdir(path[0]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
