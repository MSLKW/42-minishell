/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:42:19 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/16 16:58:58 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Find where the command path is in the many bins dictated by PATH in envp
*/
char	*find_cmd_path(char *cmd, t_lst *env_var_lst)
{
	int		index;
	char	*uncut_path;
	char	**envp_paths;
	char	*dir_path;
	char	*full_path;

	uncut_path = get_env_var_value("PATH", env_var_lst);
	// printf("uncut_path: %s\n", uncut_path);
	if (uncut_path == NULL)
		return (NULL);
	envp_paths = ft_split(uncut_path, ':');
	index = 0;
	while (envp_paths[index] != NULL)
	{
		// printf("envp_paths[%i]: %s\n", index, envp_paths[index]);
		index++;
	}
	index = 0;
	while (envp_paths[index] != NULL)
	{
		dir_path = ft_strjoin(envp_paths[index], "/");
		full_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(full_path, F_OK) == 0)
		{
			free_str_arr(envp_paths);
			return (full_path);
		}
		free(full_path);
		index++;
	}
	free_str_arr(envp_paths);
	return (NULL);
}
