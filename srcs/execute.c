/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:42:19 by maxliew           #+#    #+#             */
/*   Updated: 2025/03/05 20:49:34 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Find where the command path is in the many bins dictated by PATH in envp
*/
char	*find_cmd_path(char *cmd, char *envp[])
{
	int		index;
	char	**envp_paths;
	char	*dir_path;
	char	*full_path;

	index = 0;
	while (ft_strnstr(envp[index], "PATH", 4) == NULL)
		index++;
	envp_paths = ft_split(envp[index] + 5, ':');
	index = 0;
	while (envp_paths[index] != NULL)
	{
		dir_path = ft_strjoin(envp_paths[index], "/");
		full_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		index++;
	}
	index = -1;
	while (envp_paths[++index] != NULL)
		free(envp_paths[index]);
	free(envp_paths);
	return (NULL);
}
