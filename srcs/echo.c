/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:09:52 by zernest           #+#    #+#             */
/*   Updated: 2025/05/25 18:38:15 by maxliew          ###   ########.fr       */
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
