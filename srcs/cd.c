/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:01:48 by zernest           #+#    #+#             */
/*   Updated: 2025/04/28 08:05:30 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_cd(char **cmd)
{
	if (!cmd[1])
	{
		printf("cd: missing argument\n");
		return (1);
	}
	if (chdir(cmd[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
