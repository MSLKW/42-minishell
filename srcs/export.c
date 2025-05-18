/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:45:01 by zernest           #+#    #+#             */
/*   Updated: 2025/05/18 16:01:02 by zernest          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int print_env(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
	return (0);
}

int	handle_export(char **args, char ***envp)
{
	int	i;
	int ret;

	i = 0;
	if (!args[1])
		return (print_env(*envp));
	
	while (args[++i])
	{
		ret = builtin_export(args[i], envp);
		if (ret != 0)
			return (ret);
	}
	return (0);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	i;

	dup = malloc(n + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n && s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	is_valid_identifier(const char *str)
{
	if (!str || (!isalpha(str[0]) && str[0] != '_'))
		return (0);
	for (int i = 1; str[i] && str[i] != '='; i++)
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
	}
	return (1);
}

int	find_env_index(char **envp, const char *key)
{
	int		i = 0;
	size_t	len = strlen(key);

	while (envp && envp[i])
	{
		if (strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int builtin_export(char *arg, char ***envp)
{
	int		i;
	char	**new_env;
	char	*key;
	char	*equal_sign;
	int		existing;

	equal_sign = ft_strchr(arg, '=');
	i = 0;
	if (!arg)
	{
		while ((*envp)[i])
			printf("declare -x %s\n", (*envp)[i]);
		return(0);
	}
	if (equal_sign)
	{
		size_t key_len = equal_sign - arg;
		key = ft_strndup(arg, key_len);
	}
	else
		key = ft_strdup(arg);
	if (!is_valid_identifier(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		free(key);
		return (1);
	}
	existing = find_env_index(*envp, key);
	if (existing != -1)
	{
		free((*envp)[existing]);
		(*envp)[existing] = strdup(arg);
		free(key);
		return (0);
	}
	i = 0;
	while (*envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(key);
		return (1);
	}
	i = -1;
	while ((*envp)[++i])
		new_env[i] = (*envp)[i];
	new_env[i] = ft_strdup(arg);
	new_env[i + 1] = NULL;
	free(*envp);
	*envp = new_env;
	free(key);
	return (0);
}
