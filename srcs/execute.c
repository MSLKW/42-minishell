/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 20:42:19 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 14:43:19 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Find where the command path is in the many bins dictated by PATH in envp
*/
char	*find_cmd_path(char *cmd, t_lst *env_var_lst)
{
	char	*uncut_path;
	char	**envp_paths;
	char	*path;

	uncut_path = get_env_var_value("PATH", env_var_lst);
	if (uncut_path == NULL)
		return (NULL);
	envp_paths = ft_split(uncut_path, ':');
	if (envp_paths == NULL)
		return (NULL);
	path = search_in_paths(cmd, envp_paths);
	free_str_arr(envp_paths);
	return (path);
}

char	*search_in_paths(char *cmd, char **paths)
{
	int		i;
	char	*dir_path;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		dir_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(dir_path, cmd);
		free(dir_path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	is_builtin(char *cmd)
{
	return (ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "env", 4) == 0
		|| ft_strncmp(cmd, "exit", 5) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "history", 8) == 0
	);
}

int	run_builtin(char **args, t_data *data)
{
	if (ft_strncmp(args[0], "pwd", 4) == 0)
		return (builtin_pwd());
	if (ft_strncmp(args[0], "echo", 5) == 0)
		return (builtin_echo(args));
	if (ft_strncmp(args[0], "cd", 3) == 0)
		return (builtin_cd(args + 1, data));
	if (ft_strncmp(args[0], "env", 4) == 0)
		return (builtin_env(data->envp));
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return (builtin_exit(args, data));
	if (ft_strncmp(args[0], "unset", 6) == 0)
		return (builtin_unset(args, &data->envp, &data->env_var_lst));
	if (ft_strncmp(args[0], "export", 7) == 0)
		return (builtin_export(args, &data->envp, data));
	if (ft_strncmp(args[0], "history", 8) == 0)
		return (builtin_history(data));
	return (1);
}
