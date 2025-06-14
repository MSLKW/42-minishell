/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 11:38:08 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/14 09:59:13 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_shell_env(t_lst *env_var_lst, char ***envp)
{
	set_shlvl(env_var_lst, envp);
	set_oldpwd_env(env_var_lst, envp);
	return (0);
}
/*
	Returns 1 on error, returns 0 on success
*/
int	set_shlvl(t_lst *env_var_lst, char ***envp)
{
	char		*shlvl_val;
	t_env_var	*new_shlvl;
	int			shlvl_num;
	char		*shlvl_num_str;

	if (env_var_lst == NULL || envp == NULL || *envp == NULL || **envp == NULL)
		return (1);
	shlvl_val = get_env_var_value("SHLVL", env_var_lst);
	shlvl_num = 1;
	if (shlvl_val != NULL)
	{
		shlvl_num = ft_atoi(shlvl_val);
		shlvl_num++;
	}
	shlvl_num_str = ft_itoa(shlvl_num);
	new_shlvl = init_env_variable("SHLVL", shlvl_num_str);
	free(shlvl_num_str);
	if (new_shlvl == NULL)
		return (1);
	new_shlvl->is_export = TRUE;
	set_env_variable(env_var_lst, new_shlvl, envp);
	return (0);
}

int	set_oldpwd_env(t_lst *env_var_lst, char ***envp)
{
	t_env_var	*old_pwd;
	t_env_var	*pwd;

	if (env_var_lst == NULL || envp == NULL || *envp == NULL || **envp == NULL)
		return (1);
	old_pwd = init_env_variable("OLDPWD", NULL);
	pwd = init_env_variable("PWD", NULL);
	if (old_pwd == NULL || pwd == NULL)
		return (1);
	pwd->is_export = TRUE;
	set_env_variable(env_var_lst, old_pwd, envp);
	set_env_variable(env_var_lst, pwd, envp);
	old_pwd->is_export = TRUE;
	return (0);
}

// int	set_shell_env(t_env_var **env_var_lst)
// {
// }
