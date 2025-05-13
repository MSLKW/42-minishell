/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_sign_expansions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:56:47 by zernest           #+#    #+#             */
/*   Updated: 2025/05/13 16:05:05 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_dollar_question(char *arg, int last_exit_code)
{
	if (!arg)
		return (NULL);
	if (ft_strncmp(arg, "$?", 3) == 0)
		return (ft_itoa(last_exit_code));
	return (ft_strdup(arg));
}
