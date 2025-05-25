/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:20:26 by zernest           #+#    #+#             */
/*   Updated: 2025/05/25 17:27:15 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isdigit_str(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == FALSE)
		{
			printf("str[i] is not a digit: %c\n", str[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_exit(char** args)
{
	int exit_status;

	exit_status = 0;
	printf("exit\n");

	if (args[1])
	{
		if (ft_isdigit_str(args[1]) == TRUE)
			exit_status = ft_atoi(args[1]);
		else
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			exit_status = 2;
		}
	}
	exit(exit_status);
}
