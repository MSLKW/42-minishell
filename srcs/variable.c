/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:47:35 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/14 20:57:17 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*init_env_variable(char *key, char *value)
{
	t_env_var	*env_var;

	env_var = ft_calloc(1, sizeof(t_env_var));
	if (env_var == NULL)
		return (NULL);
	// validate key and value
	if (ft_strlen(key) > 0 && ft_isalpha(key[0]) == TRUE && ft_isalnum_str(key) == TRUE)
	{
		env_var->key = ft_strdup(key);
		env_var->value = ft_strdup(value);
		return (env_var);
	}
	return (NULL);
}

void	set_env_variable(t_lst *env_var_lst, t_env_var *env_var)
{
	t_lst	*head;
	t_env_var	*list_env_var;

	if (env_var == NULL)
		return ;
	if (env_var_lst->content == NULL)
		env_var_lst = ft_lstremove(env_var_lst, NULL, free);
	head = env_var_lst;
	while (head != NULL)
	{
		list_env_var = env_var_lst->content;
		if (ft_strncmp(env_var->key, list_env_var->key, ft_strlen(list_env_var->key) + 1) == 0)
		{
			free(list_env_var->value);
			list_env_var->value = ft_strdup(env_var->value);
			free_env_var(env_var);
			free(env_var);
			return ;
		}
		head = head->next;
	}
	ft_lstadd_back(&env_var_lst, ft_lstnew(env_var));
}

t_env_var	*get_env_variable(char *key, t_lst *env_var_lst)
{
	t_lst	*head;
	t_env_var	*env_var;

	head = env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (ft_strncmp(env_var->key, key, ft_strlen(env_var->key) + 1) == 0)
			return (env_var);
		head = head->next;
	}
	return (NULL);
}

int	unset_env_variable(char *key, t_lst **env_var_lst)
{
	t_lst	*head;
	t_env_var	*env_var;
	t_lst	*prev_lst;

	head = *env_var_lst;
	while (head != NULL)
	{
		env_var = head->content;
		if (ft_strncmp(env_var->key, key, ft_strlen(env_var->key) + 1) == 0)
		{
			prev_lst = ft_lstgetprevious(env_var_lst, head);
			if (prev_lst != NULL)
				ft_lstremove(head, prev_lst, free_env_var);
			else if (prev_lst == NULL)
				*env_var_lst = ft_lstremove(head, prev_lst, free_env_var);
			return (0);
		}
		head = head->next;
	}
	return (1);
}

void	free_env_var(void *content)
{
	t_env_var	*env_var;

	env_var = (t_env_var *)content;
	free(env_var->key);
	free(env_var->value);
}

// debug

void	display_env_var(t_data *data)
{
	t_lst		*head;
	t_env_var	*env_var;
	
	head = data->env_var_lst;
	while (head != NULL)
	{
		if (head->content == NULL)
		{
			head = head->next;
			printf("null content, go next\n");
			continue;
		}
		env_var = head->content;
		printf("display | env_var key: %s | value: %s\n", env_var->key, env_var->value);
		head = head->next;
	}
}
