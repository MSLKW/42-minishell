/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 08:01:48 by zernest           #+#    #+#             */
/*   Updated: 2025/06/03 18:18:18 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Sets oldpwd and newpwd to $OLDPWD and $PWD environment variables, 
	then frees oldpwd and newpwd.
*/
static void	set_env_pwds(char *oldpwd, char *newpwd, t_data *data)
{
	t_env_var	*oldpwd_var;
	t_env_var	*newpwd_var;

	if (oldpwd != NULL)
	{
		oldpwd_var = init_env_variable("OLDPWD", oldpwd);
		if (oldpwd_var != NULL)
		{
			oldpwd_var->is_export = TRUE;
			set_env_variable(data->env_var_lst, oldpwd_var, &data->envp);
		}
		free(oldpwd);
	}
	if (newpwd != NULL)
	{
		newpwd_var = init_env_variable("PWD", newpwd);
		if (newpwd_var != NULL)
		{
			newpwd_var->is_export = TRUE;
			set_env_variable(data->env_var_lst, newpwd_var, &data->envp);
		}
		free(newpwd);
	}
}

static char	*get_change_cwd(char **args, t_data *data)
{
	char		*change_cwd;

	if (!args || !args[0])
	{
		change_cwd = get_env_var_value("HOME", data->env_var_lst);
		if (change_cwd == NULL)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else
		change_cwd = args[0];
	return (change_cwd);
}

/*
	Sets OLDPWD to environment rl_dump_variables
*/
int	builtin_cd(char **args, t_data *data)
{
	char	*oldpwd;
	char	*newpwd;
	char	*change_cwd;
	char	*err_msg;

	change_cwd = get_change_cwd(args, data);
	if (change_cwd == NULL)
		return (1);
	if (count_null_terminated_arr(args) > 1)
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	oldpwd = getcwd(NULL, 0);
	if (ft_strlen(change_cwd) > 0 && chdir(change_cwd) != 0)
	{
		err_msg = ft_strjoin("cd: ", change_cwd);
		perror(err_msg);
		free(err_msg);
		return (1);
	}
	newpwd = getcwd(NULL, 0);
	set_env_pwds(oldpwd, newpwd, data);
	return (0);
}
