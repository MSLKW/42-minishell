/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:46:49 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/20 16:19:20 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*tokenize_line(char *line, t_data *data)
{
	int	index;
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
	assign_cmd_opt_arg_type(&token_list, data);
	assign_redirection_type(&token_list);
	assign_adjacent_whitespace(&token_list);
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
	if (content == NULL || ft_strlen(content) == 0)
		return (NULL);
	token->content = variable_expansion(content, data);
	token->handler = DQUOTE;
	token->primary_type = get_primary_token_type(token->content);
	token->secondary_type = NOTHING;
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
	if (content == NULL || ft_strlen(content) == 0)
		return (NULL);
	token->content = content;
	token->handler = SQUOTE;
	token->primary_type = get_primary_token_type(content);
	token->secondary_type = NOTHING;
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
	if (content == NULL || ft_strlen(content) == 0)
		return (NULL);
	token->content = variable_expansion(content, data);
	token->handler = NONE;
	token->primary_type = get_primary_token_type(token->content);
	token->secondary_type = NOTHING;
	(*index) += size;
	return (token);
}

t_bool	is_token_cmd(char *content, char *envp[])
{
	char	*cmd_path;

	cmd_path = find_cmd_path(content, envp);
	if (cmd_path == NULL)
		return (FALSE);
	return (TRUE);
}

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

t_bool	is_token_executable(char *content)
{
	if (ft_strlen(content) >= 2 && content[0] == '.' && content[1] == '/')
		return (TRUE);
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

t_bool	is_token_setvalue(char *content)
{
	t_env_var	*env_var;

	if (ft_strchr(content, '=') != NULL)
	{
		env_var = split_setvalue(content);
		if (env_var != NULL)
		{
			free(env_var);
			return (TRUE);
		}
	}
	return (FALSE);
}

enum primary_token_type	get_primary_token_type(char *content)
{
	int	size;
	int	index;

	size = ft_strlen(content);
	index = 0;
	if (size == 0)
		return (ERROR);
	if (content[index] == ' ')
		return (WHITESPACE);
	else if (is_token_setvalue(content) == TRUE)
		return (SET_VALUE); // variable first letter needs to be alpha, then variable itself needs to be alphanum, value can be ASCII
	else if (ft_strchr(content, '|') && size == 1)
		return (PIPE);
	else if ((ft_strchr(content, '<') || ft_strchr(content, '>')) && size == 1)
		return (REDIRECTION);
	else if ((ft_strnstr(content, ">>", size) || ft_strnstr(content, "<<", size)) && size == 2)
		return (REDIRECTION);
	// else if (size >= 2 && content[0] == '$' && ft_isalpha_str(content + 1) == TRUE)
	// 	return (VARIABLE);
	else if (ft_isalnum_str(content) == TRUE)
		return (ALPHANUMERIC);
	return (ASCII);
}
/*
	Modifies the **token_list's token types to more suitable token types like COMMAND, OPTION and ARGUMENT
*/
t_lst    *assign_cmd_opt_arg_type(t_lst **token_list, t_data *data)
{
	int    cmd_line_flag;
	t_lst    *head;
	t_token    *token;

	cmd_line_flag = 0;
	head = *token_list;
	while (head != NULL)
	{
		token = head->content;
		if (token->primary_type != WHITESPACE)
		{
			if ((token->primary_type == ALPHANUMERIC || token->primary_type == ASCII ) && cmd_line_flag == 0)
			{
				if (is_token_cmd(token->content, data->envp) == TRUE || is_token_builtin(token->content) == TRUE || is_token_executable(token->content) == TRUE)
				{
					token->secondary_type = COMMAND;
					cmd_line_flag = 1;
				}
			}
			// else if (token->primary_type == ASCII && cmd_line_flag == 0 && )
			// {

			// }
			// else if (token->primary_type == ASCII && cmd_line_flag == 1)
			// {
			//     if (is_token_option(token->content) == TRUE)
			//         token->secondary_type = ARGUMENT; // SUPPOSED TO BE OPTION BUT TURNED ARGUMENT
			// }
			else if ((token->primary_type == ALPHANUMERIC || token->primary_type == ASCII || token->primary_type == SET_VALUE) 
				&& cmd_line_flag == 1)
				token->secondary_type = ARGUMENT;
			else
				cmd_line_flag = 0;
		}
		head = head->next;
	}
	return (*token_list);
}

t_lst	**assign_redirection_type(t_lst	**token_list)
{
	t_lst	*head;
	t_token	*token;
	int		size;

	if (token_list == NULL || *token_list == NULL)
		return (NULL);
	head = *token_list;
	while (head != NULL)
	{
		token = head->content;
		if (token->primary_type == REDIRECTION)
		{
			size = ft_strlen(token->content);
			if (ft_strchr(token->content, '<') && size == 1)
				token->secondary_type = REDIRECTION_INPUT;
			else if (ft_strchr(token->content, '>') && size == 1)
				token->secondary_type = REDIRECTION_OUTPUT;
			else if (ft_strnstr(token->content, ">>", size) && size == 2)
				token->secondary_type = REDIRECTION_APPEND;
			else if (ft_strnstr(token->content, "<<", size) && size == 2)
				token->secondary_type = REDIRECTION_DELIMITER;
		}
		head = head->next;
	}
	return (token_list);
}

void	assign_adjacent_whitespace(t_lst **token_list)
{
	t_lst	*head;
	t_token	*token;
	t_token	*adj_token;

	head = *token_list;
	while (head != NULL)
	{
		token = head->content;
		if (token != NULL)
		{
			token->right_white_space = FALSE;
			token->left_white_space = FALSE;
			if (head->next != NULL)
			{
				adj_token = head->next->content;
				if (adj_token != NULL && adj_token->primary_type == WHITESPACE)
					token->right_white_space = TRUE;
			}
			if (ft_lstgetprevious(token_list, head) != NULL)
			{
				adj_token = ft_lstgetprevious(token_list, head)->content;
				if (adj_token != NULL && adj_token->primary_type == WHITESPACE)
					token->left_white_space = TRUE;
			}
		}
		head = head->next;
	}
}
