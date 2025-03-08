/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:32 by maxliew           #+#    #+#             */
/*   Updated: 2025/03/08 18:48:25 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ===== Libraries =====

// System Libraries ( Ref System Libraries Document for more information )
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

// Custom Libraries
# include "../libft/libft.h"

// Custom Macros

# define TRUE 1
# define FALSE 0

// ===== Minishell Types =====

typedef int t_bool;

// ===== Minishell Structures =====

enum	token_handler {
	NONE,
	DQUOTE,
	SQUOTE
};

enum 	token_type {
	ERROR,
	WHITESPACE,
	ALPHANUMERIC,
	ASCII,
	SET_VALUE,
	PIPE,
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	REDIRECTION_APPEND,
	REDIRECTION_DELIMITER,
	VARIABLE,
};

typedef struct s_token {
	char			*content;
	enum token_handler	handler;
	enum token_type	type;
}	t_token;

typedef struct s_ast {
	t_token	*token;
	t_list	*node_list;
} t_ast;

// ===== Minishell Functions =====

// parse.c
char	*ft_get_line(void);
t_bool	is_line_quote_ended(char *line, t_bool is_subshell, int *index);
void	debug_token_list(t_list *token_list);
void	display_token(t_token *token);

// tokenize.c
t_list	*tokenize_line(char *line);
t_token	*handle_dquote(char *line, int *index);
t_token	*handle_squote(char *line, int *index);
t_token	*handle_none(char *line, int *index);
enum token_type	get_token_type(char *content);

// history.c
void	ft_show_history(void);
void	ft_clear_history(void);

// execute.c
char	*find_cmd_path(char *cmd, char *envp[]);

// helper.c
int	ft_isalpha_str(char *str);
int	ft_isalnum_str(char *str);

// ast.c
t_ast	*find_pipes(t_list	*token_list);
void	display_ast_tree(t_ast *ast_node);

#endif