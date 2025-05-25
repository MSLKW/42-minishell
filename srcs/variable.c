/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:47:35 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/25 23:00:20 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_str_valid_key(char *key)
{
	int i;

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

t_env_var	*init_env_variable(char *key, char *value)
{
	t_env_var	*env_var;

	env_var = ft_calloc(1, sizeof(t_env_var));
	if (env_var == NULL || key == NULL)
		return (NULL);
	if (is_str_valid_key(key) == TRUE)
	{
		env_var->key = ft_strdup(key);
		if (value != NULL)
			env_var->value = ft_strdup(value);
		else if (value == NULL)
			env_var->value = ft_strdup("");
		env_var->is_export = FALSE;
		return (env_var);
	}
	return (NULL);
}

t_env_var	*split_setvalue(char *content)
{
	char	*key;
	char	*value;
	int		i;

	if (ft_strchr(content, '=') == NULL)
		return (NULL);
	i = 0;
	while (content[i] != '\0' && content[i] != '=')
		i++;
	key = ft_substr(content, 0, i);
	value = ft_substr(content, i + 1, ft_strlen(content));
	if (key == NULL)
		return (NULL);
	return (init_env_variable(key, value));
}


/*
	Frees env_var after use if used to set, returns pointer to env_var in env_var_lst
*/
t_env_var	*set_env_variable(t_lst *env_var_lst, t_env_var *env_var, char **envp)
{
	t_env_var	*list_env_var;

	if (env_var == NULL)
		return (NULL);
	list_env_var = get_env_variable(env_var->key, env_var_lst);
	if (list_env_var != NULL)
	{
		free(list_env_var->value);
		list_env_var->value = ft_strdup(env_var->value);
		if (list_env_var->is_export == FALSE)
			list_env_var->is_export = env_var->is_export;
		free_env_var(env_var);
		free(env_var);
		ft_exportcheck(list_env_var, envp);
		return (list_env_var);
	}
	ft_lstadd_back(&env_var_lst, ft_lstnew(env_var));
	ft_exportcheck(env_var, envp);
	return (env_var);
}

char	*get_env_var_value(char *key, t_lst *env_var_lst)
{
	t_env_var	*env_var;

	env_var = get_env_variable(key, env_var_lst);
	if (env_var == NULL)
		return (NULL);
	return (env_var->value);
}

t_env_var	*get_env_variable(char *key, t_lst *env_var_lst)
{
	t_lst	*head;
	t_env_var	*env_var;

	head = env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (env_var != NULL)
			if (ft_strncmp(env_var->key, key, ft_strlen(env_var->key) + 1) == 0)
				return (env_var);
		head = head->next;
	}
	return (NULL);
}

int	unset_env_variable(char *key, t_lst **env_var_lst)
{
	t_lst		*head;
	t_env_var	*env_var;
	t_lst		*prev_lst;

	head = *env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (env_var != NULL)
		{
			if (ft_strncmp(env_var->key, key, ft_strlen(env_var->key) + 1) == 0)
			{
				prev_lst = ft_lstgetprevious(env_var_lst, head);
				if (prev_lst != NULL)
					ft_lstremove(head, prev_lst, free_env_var);
				else if (prev_lst == NULL)
					*env_var_lst = ft_lstremove(head, prev_lst, free_env_var);
				return (0);
			}
		}
		head = head->next;
	}
	return (1);
}

void	free_env_var(void *content)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)content;
	if (env_var != NULL)
	{
		free(env_var->key);
		free(env_var->value);
	}
}

// debug

void	display_env_var(t_data *data)
{
	t_lst		*head;
	t_env_var	*env_var;
	
	printf("---env_var---\n");
	head = data->env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (env_var != NULL)
		{
			printf("display | env_var: %p | env_var key: %s | value: %s\n", env_var, env_var->key, env_var->value);
		}
		else
		{
			printf("env_var is null\n");
		}
		head = head->next;
	}
	printf("-------------\n");
}
