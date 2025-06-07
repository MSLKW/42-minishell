/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 17:56:43 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/06 18:03:15 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_str_valid_key(char *key)
{
	int	i;

	if (key == NULL)
		return (FALSE);
	if (ft_strlen(key) > 0 && ft_isalpha(key[0]) == TRUE)
	{
		i = 0;
		while (key[i] != '\0')
		{
			if (ft_isalnum(key[i]) == FALSE && key[i] != '_')
				return (FALSE);
			i++;
		}
		return (TRUE);
	}
	return (FALSE);
}

char	*get_env_var_value(char *key, t_lst *env_var_lst)
{
	t_env_var	*env_var;

	env_var = get_env_variable(key, env_var_lst);
	if (env_var == NULL)
		return (NULL);
	return (env_var->value);
}

t_env_var	*split_assignment(char *content)
{
	char		*key;
	char		*value;
	int			i;
	t_env_var	*result;

	if (ft_strchr(content, '=') == NULL)
		return (NULL);
	i = 0;
	while (content[i] != '\0' && content[i] != '=')
		i++;
	key = ft_substr(content, 0, i);
	value = ft_substr(content, i + 1, ft_strlen(content));
	if (key == NULL)
		return (NULL);
	result = init_env_variable(key, value);
	free(key);
	free(value);
	return (result);
}
