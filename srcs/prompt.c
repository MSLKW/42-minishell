/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:17:20 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/18 15:17:51 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_prompt(t_data *data)
{
	char	*cwd;
	char	*dir;
	char	*prompt;
	char	*prompt_env;

	cwd = ft_get_prompt_cwd(data);
	if (cwd == NULL)
		return (NULL);
	prompt_env = ft_get_prompt_environment();
	dir = ft_strjoin(cwd, "\033[0m$ ");
	free(cwd);
	if (prompt_env == NULL)
		return (dir);
	prompt = ft_strjoin(prompt_env, dir);
	free(dir);
	free(prompt_env);
	return (prompt);
}

/*
	HOME=/home/msl
	will replace it when it shouldn't 
	/home/mslkw/directory -> ~kw/directory
*/
char	*ft_get_prompt_cwd(t_data *data)
{
	char	*cwd;
	char	*home_cwd;
	int		start_i;
	char	*dir_minus_home;

	home_cwd = get_env_var_value("HOME", data->env_var_lst);
	cwd = getcwd(NULL, 0);
	if (home_cwd == NULL || cwd == NULL)
		return (cwd);
	if (ft_strlen(home_cwd) > 0 && \
ft_strnstr(cwd, home_cwd, ft_strlen(cwd)) != NULL)
	{
		start_i = ft_strlen(home_cwd);
		dir_minus_home = ft_substr(cwd, start_i, ft_strlen(cwd) - start_i);
		free(cwd);
		cwd = ft_strjoin("~", dir_minus_home);
		free(dir_minus_home);
	}
	return (cwd);
}

static char	*combine_prompt(char *name, char *logname)
{
	char	*part0;
	char	*part1;
	char	*part2;
	char	*part3;

	part0 = ft_strjoin("\033[32m", logname);
	part1 = ft_strjoin(part0, "@");
	part2 = ft_strjoin(part1, name);
	part3 = ft_strjoin(part2, "\033[0m:\033[36m");
	free(part0);
	free(part1);
	free(part2);
	return (part3);
}

char	*ft_get_prompt_environment(void)
{
	char	*name_env;
	char	*logname_env;

	name_env = getenv("NAME");
	logname_env = getenv("LOGNAME");
	if (name_env == NULL || logname_env == NULL)
		return (NULL);
	return (combine_prompt(name_env, logname_env));
}
