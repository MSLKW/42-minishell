/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:20:26 by zernest           #+#    #+#             */
/*   Updated: 2025/06/18 17:28:02 by maxliew          ###   ########.fr       */
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
		if (ft_isdigit(str[i]) == FALSE && str[i] != '-' && str[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

void	free_exit(int exit_status, t_data *data)
{
	free_data(data);
	exit(exit_status);
}

int	builtin_exit(char **args, t_data *data)
{
	int	exit_status;

	printf("exit\n");
	if (args[1])
	{
		if (ft_isdigit_str(args[1]) == FALSE)
		{
			ft_put_error(args[1], "numeric argument required");
			data->last_exit_code = 2;
			data->should_exit = 1;
			return (data->last_exit_code);
		}
		if (args[2])
		{
			ft_put_error("exit", "too many arguments");
			data->last_exit_code = 1;
			return (data->last_exit_code);
		}
		exit_status = ft_atoi(args[1]);
	}
	else
		exit_status = data->last_exit_code;
	data->last_exit_code = exit_status;
	data->should_exit = 1;
	return (exit_status);
}
