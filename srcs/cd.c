/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:01:48 by zernest           #+#    #+#             */
/*   Updated: 2025/05/13 15:26:59 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	builtin_cd(char **cmd)
// {
// 	if (!cmd[1])
// 	{
// 		printf("cd: missing argument\n");
// 		return (1);
// 	}
// 	if (chdir(cmd[1]) != 0)
// 	{
// 		perror("cd");
// 		return (1);
// 	}
// 	return (0);
// }

// int builtin_cd(char **args)
// {
// 	const char	*target;

// 	if (!args[1])
// 		target = getenv("HOME");
// 	else
// 		target = args[1];
// 	if (!target)
// 	{
// 		ft_putstr_fd("cd: HOME not set\n", 2);
// 		return (1);
// 	}
// 	if (chdir(target) != 0)
// 	{
// 		perror("cd");
// 		return (1);
// 	}
// 	return (0);
// }

// int	builtin_cd(char *cmd)
// {
// 	if (!cmd) // no argument → go to $HOME
// 	{
// 		cmd = getenv("HOME");
// 		if (!cmd)
// 		{
// 			printf("cd: HOME not set\n");
// 			return (1);
// 		}
// 	}

// 	if (chdir(cmd) != 0)
// 	{
// 		perror("cd");
// 		return (1);
// 	}
// 	return (0);
// }

// int builtin_cd(char **cmd)
// {
// 	char cwd[1024];
// 	if (getcwd(cwd, sizeof(cwd)))
// 		printf("Starting cwd: %s\n", cwd);
// 	else
// 		perror("getcwd");

// 	if (!cmd || !cmd[1]) // no argument → cd
// 	{
// 		char *home = getenv("HOME");
// 		if (!home)
// 		{
// 			printf("cd: HOME not set\n");
// 			return (1);
// 		}
// 		if (chdir(home) != 0)
// 		{
// 			perror("cd");
// 			return (1);
// 		}
// 		return (0);
// 	}
// 	if (chdir(cmd[1]) != 0)
// 	{
// 		perror("cd");
// 		return (1);
// 	}
// 	return (0);
// }

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
