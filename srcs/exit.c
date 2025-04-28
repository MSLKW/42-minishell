/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:20:26 by zernest           #+#    #+#             */
/*   Updated: 2025/04/28 15:28:31 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_exit(char** args)
{
	int exit_status;

	exit_status = 0;
	printf("exit\n");

	if (args[1] && args[2])
	{
		printf("exit: too man arguments");
		return (1);
	}
	if (args[1])
		exit_status = ft_atoi(args[1]);
	exit(exit_status);
}
