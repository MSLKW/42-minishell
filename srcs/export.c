/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:45:01 by zernest           #+#    #+#             */
/*   Updated: 2025/05/25 22:37:06 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int print_env(char **envp)
// {
// 	int i = 0;
// 	while (envp[i])
// 	{
// 		printf("declare -x %s\n", envp[i]);
// 		i++;
// 	}
// 	return (0);
// }

// int	handle_export(char **args, char ***envp)
// {
// 	int	i;
// 	int ret;

// 	i = 0;
// 	if (!args[1])
// 		return (print_env(*envp));
	
// 	while (args[++i])
// 	{
// 		ret = builtin_export(args[i], envp);
// 		if (ret != 0)
// 			return (ret);
// 	}
// 	return (0);
// }

// char	*ft_strndup(const char *s, size_t n)
// {
// 	char	*dup;
// 	size_t	i;

// 	dup = malloc(n + 1);
// 	if (!dup)
// 		return (NULL);
// 	i = 0;
// 	while (i < n && s[i])
// 	{
// 		dup[i] = s[i];
// 		i++;
// 	}
// 	dup[i] = '\0';
// 	return (dup);
// }

// int	is_valid_identifier(const char *str)
// {
// 	if (!str || (!isalpha(str[0]) && str[0] != '_'))
// 		return (0);
// 	for (int i = 1; str[i] && str[i] != '='; i++)
// 	{
// 		if (!isalnum(str[i]) && str[i] != '_')
// 			return (0);
// 	}
// 	return (1);
// }

int	find_env_index(char **envp, const char *key)
{
	int			i;
	t_env_var	*env_var;
	
	if (key == NULL || envp == NULL)
		return (-1);
	i = 0;
	while (envp[i] != NULL)
	{
		env_var = split_setvalue(envp[i]);
		if (env_var != NULL)
		{
			if (ft_strncmp(env_var->key, key, \
				ft_strlen(env_var->key) + 1) == 0)
				return (i);
		}
		i++;
	}
	return (-1);
}

// int builtin_export(char *arg, char ***envp)
// {
// 	char *equal_sign = strchr(arg, '=');
// 	char *key = NULL;
// 	int i = 0;
// 	int existing;

// 	if (equal_sign)
// 		key = strndup(arg, equal_sign - arg);
// 	else
// 		key = strdup(arg);
// 	if (!is_valid_identifier(key)) {
// 		fprintf(stderr, "export: `%s': not a valid identifier\n", key);
// 		free(key);
// 		return 1;
// 	}
// 	existing = find_env_index(*envp, key);
// 	free(key);
// 	if (existing != -1) {
// 		free((*envp)[existing]);
// 		(*envp)[existing] = strdup(arg);
// 		return 0;
// 	}
// 	while ((*envp)[i])
// 		i++;
// 	char **new_env = malloc(sizeof(char *) * (i + 2));
// 	if (!new_env)
// 		return 1;
// 	i = 0;
// 	while ((*envp)[i]) {
// 		new_env[i] = (*envp)[i];
// 		i++;
// 	}
// 	new_env[i] = strdup(arg);
// 	new_env[i + 1] = NULL;
// 	free(*envp);
// 	*envp = new_env;
// 	return 0;
// }

/*
	args must be NULL-TERMINATED
*/
// static int	count_args(char **args)
// {
// 	int	count;

// 	count = 0;
// 	while (args[count] != NULL)
// 		count++;
// 	return (count);
// }

char	*join_export_identifer(char *key, char *value)
{
	char	*part1;
	char	*part2;

	if (key == NULL || value == NULL)
		return (NULL);
	part1 = ft_strjoin(key, "=");
	part2 = ft_strjoin(part1, value);
	free(part1);
	return (part2);
}

/*
	It kind of overwrites something? idk what tho. 
	feels unsafe asf but it works
*/
int	ft_addenv(char *arg, char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		i++;
	}
	envp[i] = arg;
	i++;
	envp[i] = NULL;
	return (0);
}

int	ft_setenv(char *key, char *value, char **envp)
{
	int env_index;
	
	env_index = find_env_index(envp, key);
	if (env_index == -1)
	{
		ft_addenv(join_export_identifer(key, value), envp);
		return (0);
	}
	free(envp[env_index]);
	envp[env_index] = join_export_identifer(key, value);
	return (0);
}

char	*ft_getenv(char *key, char **envp)
{
	int 		env_index;
	t_env_var	*env_var;
	
	env_index = find_env_index(envp, key);
	if (env_index == -1)
		return (NULL);
	env_var = split_setvalue(envp[env_index]);
	if (env_var == NULL)
		return (NULL);
	return (env_var->value);
}

int	ft_exportcheck(t_env_var *var, char **envp)
{
	if (var == NULL)
		return (1);
	if (var->value != NULL && var->is_export == TRUE)
	{
		ft_setenv(var->key, var->value, envp);
		return (0);
	}
	return (1);
}

int	process_args(char **args, char ***envp, t_lst *env_var_lst)
{
	int			i;
	t_env_var	*var;

	i = 1;
	while (args[i] != NULL)
	{
		// "export var=value"
		var = split_setvalue(args[i]);
		if (var != NULL)
		{
			var->is_export = TRUE;
			var = set_env_variable(env_var_lst, var, *envp);
		}
		else
		{
			// "var=5, export var"
			var = get_env_variable(args[i], env_var_lst);
			if (var != NULL)
			{
				var->is_export = TRUE;
				ft_exportcheck(var, *envp);
			}
			else if (var == NULL)
			{
				// "export var, var=5"
				var = init_env_variable(args[i], NULL);
				if (var == NULL)
				{
					printf("\'%s\' is not a valid identifier\n", args[i]);
					break ;
				}
				var = set_env_variable(env_var_lst, var, *envp);
				var->is_export = TRUE;
			}
		}
		i++;
	}
	return (0);
}

int	builtin_export(char **args, char ***envp, t_data *data)
{
	// validate args to have only 1 argument
	process_args(args, envp, data->env_var_lst);
	// builtin_env(*envp);
	return (0);
}

// export
// how to put in env and variable expansion needs to get from envp too
// updating envp??