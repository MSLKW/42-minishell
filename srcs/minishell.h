/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:32 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/05 22:43:50 by maxliew          ###   ########.fr       */
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

enum 	primary_token_type {
	ERROR,
	WHITESPACE,
	ALPHANUMERIC,
	ASCII,
	SET_VALUE,
	PIPE,
	REDIRECTION,
	VARIABLE,
};

enum	secondary_token_type {
	NOTHING,
	COMMAND,
	OPTION, // NOT USED
	ARGUMENT,
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	REDIRECTION_APPEND,
	REDIRECTION_DELIMITER,
};

typedef struct s_token {
	char			*content;
	enum	token_handler	handler;
	enum	primary_token_type	primary_type;
	enum	secondary_token_type secondary_type;
}	t_token;

typedef struct s_ast {
	t_token	*token;
	t_lst	*node_list;
} t_ast;

typedef struct	s_data {
	int		argc;
	char	**argv;
	char	**envp;
} t_data;

// ===== Minishell Functions =====

// parse.c
char	*ft_get_line(void);
t_bool	is_line_quote_ended(char *line, t_bool is_subshell, int *index);

// tokenize.c
t_lst	*tokenize_line(char *line, t_data *data);
t_token	*handle_dquote(char *line, int *index);
t_token	*handle_squote(char *line, int *index);
t_token	*handle_none(char *line, int *index);
enum primary_token_type	get_primary_token_type(char *content);
t_lst	*assign_cmd_opt_arg_type(t_lst	**token_list, t_data *data);
t_lst	**assign_redirection_type(t_lst	**token_list);

// history.c
void	ft_show_history(void);
void	ft_clear_history(void);

// execute.c
char	*find_cmd_path(char *cmd, char *envp[]);

// helper.c
int	ft_isalpha_str(char *str);
int	ft_isalnum_str(char *str);

// ast_init.c
t_ast	*find_pipes(t_lst	*token_list);
t_ast	*init_ast(t_lst	**token_list);
t_ast	*init_pipe(t_lst **token_list, t_lst *pipe_token);
t_ast	*init_redirection(t_lst **token_list, t_lst *redirection_token);
t_ast	*init_input_redirection(t_lst **token_list, t_lst *redirection_token);
t_ast	*init_output_redirection(t_lst **token_list, t_lst *redirection_token);
t_ast	*init_command(t_lst	*command_token);
t_ast	*init_argument(t_lst *argument_token);

// ast_search.c
t_lst	*find_primary_token_right(t_lst *current_token_lst, enum primary_token_type token_type, int	size);
t_lst	*find_primary_token_left(t_lst	**token_list, t_lst *current_token_lst, enum primary_token_type token_type, int size);
t_lst	*find_secondary_token_right(t_lst *current_token_lst, enum secondary_token_type token_type, int size);
t_lst	*find_secondary_token_left(t_lst	**token_list, t_lst *current_token_lst, enum secondary_token_type token_type, int size);

// interactive_mode.c
void	ctrlc_handler(int sig);
void	ctrld_handler(void);

// debug.c
void	ft_display(t_lst *list);
void	debug_token_list(t_lst *token_list);
void	display_token(t_token *token);
void	display_token_handler(enum token_handler handler);
void	display_primary_token_type(enum primary_token_type type);
void	display_secondary_token_type(enum secondary_token_type type);
void	display_ast_tree(t_ast *ast_node);

// BUILTINS --
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_cd(char **cmd);
int		builtin_env(char **envp);
int		builtin_exit(char** args);
int		builtin_unset_env(char *key, char ***envp_copy);

#endif