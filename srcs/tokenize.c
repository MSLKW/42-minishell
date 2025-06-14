/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:46:49 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/14 15:06:24 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*init_token(char *content, enum token_handler handler, t_flag *flags)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (token == NULL || content == NULL)
		return (NULL);
	token->content = ft_strdup(content);
	token->handler = handler;
	if (flags == NULL)
		token->flags = init_empty_token_flags();
	else
		token->flags = token_dup_flag(flags);
	return (token);
}


t_lst	*tokenize_line(char *line, t_data *data)
{
	t_lst	*token_list;
	t_lst	*new_token_list;

	token_list = tokenize_str(line);
	if (token_list == NULL)
		return (NULL);

	expand_variable_token_list(token_list, data);
	if (DEBUG == 1)
	{
		printf("token_list\n");
		debug_token_list(token_list);
	}

	new_token_list = split_token_none(&token_list);
	ft_lstclear(&token_list, free_token);
	token_list = new_token_list;

	apply_token_flags(token_list); // reapply token flags for whitespaces
	if (DEBUG == 1)
	{
		printf("Split list\n");
		debug_token_list(token_list);
	}

	new_token_list = join_token_list(&token_list);
	if (DEBUG == 1)
	{
		printf("Join list\n");
		debug_token_list(new_token_list);
	}
	ft_lstclear(&token_list, free_token);

	assign_flags_redir_arg(new_token_list);

	assign_flags_cmd_arg(&new_token_list);
	return (new_token_list);
}

/*
	Only needs to apply this to variables instead of teh whole list
*/
t_lst	*split_token_none(t_lst **token_list)
{
	t_lst	*new_token_list;
	t_lst	*head;
	t_token	*token;
	t_lst	*list;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	new_token_list = NULL;
	head = *token_list;
	while (head != NULL)
	{
		token = head->content;
		if (token->handler == NONE && ft_has_delimiter(token->content))
		{
			list = tokenize_str(token->content); // might only need to do for none
			if (has_token_flag(token->flags, WORD))
				token_add_flags_iter(list, WORD);
			ft_lstadd_back(&new_token_list, list);
		}
		else
			ft_lstadd_back(&new_token_list, ft_lstnew(init_token(token->content, token->handler, token->flags)));
		head = head->next;
	}
	return (new_token_list);
}

t_bool	is_token_executable(char *path)
{
	int success;
	struct stat	file_stat;
	
	success = access(path, X_OK);
	if (success == 0)
	{
		stat(path, &file_stat);
		if (S_ISDIR(file_stat.st_mode))
			return (FALSE);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_token_assignment(char *content)
{
	t_env_var	*env_var;

	if (ft_strchr(content, '=') != NULL)
	{
		env_var = split_assignment(content);
		if (env_var != NULL)
		{
			free_env_var(env_var);
			return (TRUE);
		}
	}
	return (FALSE);
}
