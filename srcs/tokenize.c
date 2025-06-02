/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:46:49 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/31 23:06:18 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*tokenize_line(char *line, t_data *data)
{
	t_lst	*token_list;
	t_lst	*new_token_list;

	token_list = tokenize_str(line, data);
	if (token_list == NULL)
		return (NULL);
	// memleak
	new_token_list = split_token_none(&token_list, data);
	printf("---split_token_none---\n");
	debug_token_list(new_token_list);
	printf("---split_token_none---\n");
	new_token_list = join_token_list(&new_token_list);
	printf("---joint token list---\n");
	debug_token_list(new_token_list);
	printf("---join token list---\n");
	// figure this shit out
	// assign types properly (refactor types?)
	assign_cmd_opt_arg_type(&token_list, data);
	return (token_list);
}

t_lst	*tokenize_str(char *line, t_data *data)
{
	int		index;
	t_lst	*token_list;

	index = 0;
	token_list = NULL;
	while (line[index] != '\0')
	{
		if (line[index] == '\"')
			ft_lstadd_back(&token_list, ft_lstnew(handle_dquote(line, &index, data)));
		else if (line[index] == '\'')
			ft_lstadd_back(&token_list, ft_lstnew(handle_squote(line, &index)));
		else
			ft_lstadd_back(&token_list, ft_lstnew(handle_none(line, &index, data)));
	}
	return (token_list);
}

t_token	*handle_dquote(char *line, int *index, t_data *data)
{
	int	size;
	t_token	*token;
	char	*content;

	size = 0;
	(*index)++;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	while (line[*index + size] != '\"')
		size++;
	content = ft_substr(line, *index, size);
	if (content == NULL)
		return (NULL);
	token->content = variable_expansion(content, data);
	free(content);
	token->handler = DQUOTE;
	token->flags = init_token_flags(token->content);
	(*index) += size + 1;
	return (token);
}

t_token	*handle_squote(char *line, int *index)
{
	int	size;
	t_token	*token;
	char	*content;

	size = 0;
	(*index)++;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	while (line[*index + size] != '\'')
		size++;
	content = ft_substr(line, *index, size);
	if (content == NULL)
		return (NULL);
	token->content = content;
	token->handler = SQUOTE;
	token->flags = init_token_flags(token->content);
	(*index) += size + 1;
	return (token);
}

t_token	*handle_none(char *line, int *index, t_data *data)
{
	int	size;
	t_token	*token;
	char	*content;

	size = 0;
	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	if (line[*index + size] == ' ')
	{
		while (line[*index + size] == ' ')
			size++;
	}
	else
	{
		while (line[*index + size] != ' ' && line[*index + size] != '\"' && line[*index + size] != '\'' && line[*index + size] != '\0')
			size++;
	}
	content = ft_substr(line, *index, size);
	if (content == NULL)
		return (NULL);
	token->content = variable_expansion(content, data);
	free(content);
	token->handler = NONE;
	token->flags = init_token_flags(token->content);
	(*index) += size;
	return (token);
}

t_lst	*join_token_list(t_lst **token_list)
{
	t_lst	*head;
	t_lst	*new_token_list;
	t_token	*token;
	t_token	*new_token;
	char	*joint_content;
	char	*temp;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	new_token_list = NULL;
	head = *token_list;
	joint_content = NULL;
	while (head != NULL)
	{
		token = head->content;
		if (has_token_flag(token->flags, WHITESPACE) == FALSE)
		{
			if (joint_content == NULL)
				joint_content = ft_strdup(token->content);
			else
			{
				temp = joint_content;
				joint_content = ft_strjoin(joint_content, token->content);
				free(temp);
			}
		}
		else if (has_token_flag(token->flags, WHITESPACE) == TRUE)
		{
			new_token = malloc(sizeof(t_token));
			if (new_token == NULL)
				return (NULL);
			new_token->content = ft_strdup(joint_content);
			free(joint_content);
			joint_content = NULL;
			new_token->handler = NONE;
			new_token->flags = init_token_flags(new_token->content);
			ft_lstadd_back(&new_token_list, ft_lstnew(new_token));
		}
		head = head->next;
	}
	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (NULL);
	new_token->content = ft_strdup(joint_content);
	free(joint_content);
	joint_content = NULL;
	new_token->handler = NONE;
	new_token->flags = init_token_flags(new_token->content);
	ft_lstadd_back(&new_token_list, ft_lstnew(new_token));
	return (new_token_list);
}

t_lst	*split_token_none(t_lst **token_list, t_data *data)
{
	t_lst	*new_token_list;
	t_lst	*head;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	new_token_list = NULL;
	head = *token_list;
	while (head != NULL)
	{
		t_token *token = head->content;
		if (token->handler == NONE)
		{
			ft_lstadd_back(&new_token_list, tokenize_str(token->content, data)); // might need to do only for none.
		}
		else
		{
			ft_lstadd_back(&new_token_list, ft_lstnew(token)); // there's very finnicky memory problems here if trying to free
		}
		head = head->next;
	}
	return (new_token_list);
}

// t_bool	is_token_cmd(char *content, char *envp[])
// {
// 	char	*cmd_path;

// 	cmd_path = find_cmd_path(content, envp);
// 	if (cmd_path == NULL)
// 		return (FALSE);
// 	return (TRUE);
// }

t_bool	is_token_builtin(char *content)
{
	if (ft_strncmp(content, "echo", ft_strlen(content)) == 0 ||
		ft_strncmp(content, "cd", ft_strlen(content)) == 0 ||
		ft_strncmp(content, "pwd", ft_strlen(content)) == 0 ||
		ft_strncmp(content, "export", ft_strlen(content)) == 0 ||
		ft_strncmp(content, "unset", ft_strlen(content)) == 0 ||
		ft_strncmp(content, "env", ft_strlen(content)) == 0 ||
		ft_strncmp(content, "exit", ft_strlen(content)) == 0 ||
		ft_strncmp(content, "history", ft_strlen(content)) == 0
	)
		return (TRUE);
	else
		return (FALSE);
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

t_bool	is_token_option(char *content)
{
	if (content == NULL)
		return (FALSE);
	// shortform | rm -fr
	if (ft_strlen(content) > 0 && content[0] == '-')
	{
		return (TRUE);
	}
	// longform | rm --force
	// else if (ft_strlen(content) >= 2 && content[0] == '-' && content[1] == '-')
	// {
		// 	return (TRUE);
		// }
	return (FALSE);
}

t_bool	is_token_assignment(char *content)
{
	t_env_var	*env_var;

	if (ft_strchr(content, '=') != NULL)
	{
		env_var = split_setvalue(content);
		if (env_var != NULL)
		{
			free_env_var(env_var);
			return (TRUE);
		}
	}
	return (FALSE);
}

/*
	Modifies the **token_list's token types to more suitable token types like COMMAND, OPTION and ARGUMENT
*/
t_lst    *assign_cmd_opt_arg_type(t_lst **token_list, t_data *data)
{
	int    cmd_line_flag;
	t_lst    *head;
	t_token    *token;

	(void)data;
	cmd_line_flag = 0;
	head = *token_list;
	while (head != NULL)
	{
		token = head->content;
		if (has_token_flag(token->flags, WHITESPACE) == FALSE)
		{
			if (has_token_flag(token->flags, ASSIGNMENT) && cmd_line_flag == 0)
			{
				cmd_line_flag = 1;
			}
			else if (has_token_flag(token->flags, WORD) && cmd_line_flag == 0)
			{
				token_add_flag(token->flags, COMMAND);
				cmd_line_flag = 1;
			}
			else if ((has_token_flag(token->flags, WORD) || has_token_flag(token->flags, ASSIGNMENT)) && cmd_line_flag == 1)
				token_add_flag(token->flags, ARGUMENT);
			else
				cmd_line_flag = 0;
		}
		head = head->next;
	}
	return (*token_list);
}
