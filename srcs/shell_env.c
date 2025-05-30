/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:38:08 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/30 12:14:56 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	set_shell(t_env_var **env_var_lst)
// {

// }
/*
	Returns 1 on error, returns 0 on success
*/
int	set_shlvl(t_lst *env_var_lst, char ***envp)
{
	char		*shlvl_val;
	t_env_var	*new_shlvl;
	int			shlvl_num;

	if (env_var_lst == NULL || envp == NULL || *envp == NULL || **envp == NULL)
		return (1);
	shlvl_val = get_env_var_value("SHLVL", env_var_lst);
	shlvl_num = 1;
	if (shlvl_val != NULL)
	{
		shlvl_num = ft_atoi(shlvl_val);
		shlvl_num++;
	}
	new_shlvl = init_env_variable("SHLVL", ft_itoa(shlvl_num));
	if (new_shlvl == NULL)
		return (1);
	new_shlvl->is_export = TRUE;
	set_env_variable(env_var_lst, new_shlvl, envp);
	return (0);
}

// int	set_shell_env(t_env_var **env_var_lst)
// {
	
// }
