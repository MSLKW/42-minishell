/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:09:52 by zernest           #+#    #+#             */
/*   Updated: 2025/05/18 15:26:48 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *arg)
{
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	for (int i = 2; arg[i]; i++)
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	builtin_echo(char **args)
{
	int i = 1;
	int nl;

	nl = 1;
	while (args[i] && is_n_flag(args[i]))
	{
		nl = 0;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (nl)
		printf("\n");
	return (0);
}
