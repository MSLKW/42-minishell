/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:01:48 by zernest           #+#    #+#             */
/*   Updated: 2025/05/13 15:26:59 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_cd(char **args)
{
	char cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("Starting cwd: %s\n", cwd);

	if (!args || !args[0])
	{
		printf("cd: missing argument\n");
		return (1);
	}
	if (chdir(args[0]) != 0)
	{
		perror("cd failed");
		return (1);
	}

	getcwd(cwd, sizeof(cwd));
	printf("Changed cwd: %s\n", cwd);

	return (0);
}
