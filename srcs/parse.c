/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:16:06 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/17 23:50:52 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_line_reprompt(char *concat_line, t_data *data)
{
	int		index;
	char	*line_read;
	char	*new_line_read;
	char	*temp;

	index = 0;
	while (is_line_quote_ended(concat_line, FALSE, &index) == FALSE)
	{
		rl_on_new_line();
		line_read = readline("> ");
		if (!line_read)
		{
			free(concat_line);
			ctrld_handler(data);
		}
		new_line_read = ft_strjoin("\n", line_read);
		temp = ft_strjoin(concat_line, new_line_read);
		free(concat_line);
		free(new_line_read);
		free(line_read);
		concat_line = temp;
		index = 0;
	}
	return (concat_line);
}

char	*ft_get_line(t_data *data)
{
	char	*concat_line;
	char	*prompt;

	prompt = ft_get_prompt(data);
	rl_on_new_line();
	concat_line = readline(prompt);
	free(prompt);
	if (!concat_line)
		ctrld_handler(data);
	concat_line = ft_line_reprompt(concat_line, data);
	return (concat_line);
}

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

t_bool	is_line_quote_ended(char *line, t_bool is_subshell, int *index)
{
	int	quote_flag;
	int	parenthesis_count;

	quote_flag = 0;
	parenthesis_count = 0;
	while (line[*index] != '\0')
	{
		if (is_subshell == TRUE && parenthesis_count == -1)
			break ;
		if (quote_flag == 0 && line[*index] == '\'')
			quote_flag = 1;
		else if (quote_flag == 1 && line[*index] == '\'')
			quote_flag = 0;
		else if (quote_flag == 0 && line[*index] == '\"')
			quote_flag = 2;
		else if (quote_flag == 2 && line[*index] == '\"')
			quote_flag = 0;
		else if (quote_flag == 0 && line[*index] == '(')
			parenthesis_count++;
		else if (quote_flag == 0 && line[*index] == ')')
			parenthesis_count--;
		else if (ft_strlen(line) != 1 && (quote_flag != 1 && line[*index] == '$' && line[*index + 1] == '('))
		{
			(*index) += 2;
			if (is_line_quote_ended(line, TRUE, index) == FALSE)
				return (FALSE);
			continue ;
		}
		(*index)++;
	}
	if (is_subshell == TRUE && quote_flag == 0 && parenthesis_count == -1)
		return (TRUE);
	else if (is_subshell == FALSE && quote_flag == 0 && parenthesis_count == 0)
		return (TRUE);
	return (FALSE);
}
