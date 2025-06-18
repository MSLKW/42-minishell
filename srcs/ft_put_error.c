/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:47:20 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 17:02:07 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_error(char *arg, char *error_str)
{
	if (arg == NULL && error_str == NULL)
		return ;
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_str, ft_strlen(error_str));
	write(STDERR_FILENO, "\n", 1);
}