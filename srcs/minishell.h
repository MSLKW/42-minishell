/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:32 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/13 15:55:51 by maxliew          ###   ########.fr       */
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
# define TOKEN_FLAG_SIZE 14

// ===== Minishell Types =====

typedef int t_bool;

// ===== Minishell Structures =====

enum	token_handler {
	NONE,
	DQUOTE,
	SQUOTE,
	JOINT
};

typedef enum token_flag {
	NO_FLAG,
	DELIMITER,
	WHITESPACE,
	OPERATOR,
	PIPE,
	REDIRECTION,
	REDIRECTION_INPUT,
	REDIRECTION_OUTPUT,
	REDIRECTION_APPEND,
	REDIRECTION_DELIMITER,
	REDIRECTION_ARGUMENT,
	WORD,
	COMMAND,
	ARGUMENT,
	ASSIGNMENT,
} t_flag;

typedef struct s_token {
	char			*content;
	enum	token_handler	handler;
	t_flag				*flags;
}	t_token;

typedef struct s_cmd_seq {
	t_lst	*token_list;
	char	*assignment;
	char	**argv;
	t_lst	*io_list;
}	t_cmd_seq;

typedef struct s_io {
	char	*content;
	t_flag	flag;
}	t_io;

typedef struct s_env_var {
	char	*key;
	char	*value;
	t_bool	is_export;
}	t_env_var;

typedef struct	s_data {
	int		argc;
	char	**argv;
	char	**envp;
	int		last_exit_code;
	t_lst	*env_var_lst;
	char	**history;
	int		history_size;
	t_lst	*free_ptr_tokens;
	t_lst	*free_ptr_cmd_seqs;
}	t_data;

// ===== Minishell Functions =====

// minishell.c
void	shell_routine(t_data *data);
t_data	*init_data(int argc, char **argv, char **envp);
char	**get_envp_copy(char **envp, int extra);
t_lst	*init_exported_env_var_lst(char ***envp);

// shell_env.c
int		set_shlvl(t_lst *env_var_lst, char ***envp);

// parse.c
char	*ft_get_line(t_data *data);
char	*ft_get_prompt(t_data *data);
char	*ft_get_prompt_cwd(t_data *data);
char	*ft_get_prompt_environment(void);
t_bool	is_line_quote_ended(char *line, t_bool is_subshell, int *index);

// tokenize.c
t_token	*init_token(char *content, enum token_handler handler, t_flag *flags);
t_lst	*tokenize_line(char *line, t_data *data);
t_lst	*tokenize_str(char *line);
t_token	*handle_dquote(char *line, int *index);
t_token	*handle_squote(char *line, int *index);
t_token	*handle_none(char *line, int *index);
t_lst	*split_token_none(t_lst **token_list);
t_lst	*join_token_list(t_lst **token_list);
t_bool	is_token_cmd(char *content, char *envp[]);
t_bool	is_token_builtin(char *content);
t_bool	is_token_executable(char *content);
t_bool	is_token_assignment(char *content);
t_lst	*assign_flags_cmd_arg(t_lst	**token_list);
void	assign_flags_redir_arg(t_lst *token_list);
t_lst	*expand_variable_token_list(t_lst *token_list, t_data *data);

// token_flags.c
t_flag	*init_empty_token_flags(void);
t_bool	has_token_flag(t_flag *flags, t_flag flag);
t_flag	*init_token_flags(t_token *token);
int		token_add_flag(t_flag *flag_arr, t_flag flag);
int		token_add_flags(t_flag *flag_arr, t_flag *new_flag_arr);
int		token_rm_flag(t_flag *flag_arr, t_flag flag);
int		token_rm_flags(t_flag *flag_arr);
t_flag	*token_dup_flag(t_flag *flag_arr);
int		token_add_flags_iter(t_lst *token_list, t_flag flag);
int		apply_token_flags(t_lst	*token_list);
int		count_token_with_flag(t_lst	*token_list, t_flag flag);

// history.c
// void	ft_show_history(void);
// void	ft_clear_history(void);

// execute.c
char	*find_cmd_path(char *cmd, t_lst *env_var_lst);
void	execute_builtin(char *cmd_name, char **args, t_data *data);
char	**get_args_from_ast(t_lst *node_list);

// execute_new.c
int		execute_command(t_cmd_seq *cmd_seq, t_data *data);
int		execute_cmd_seqs(t_lst *cmd_seqs, t_data *data);
int		execute_assignment(t_cmd_seq *cmd_seq, t_data *data);

// helper.c
int		ft_isalpha_str(char *str);
int		ft_isalnum_str(char *str);
int		count_null_terminated_arr(char **str_arr);
t_bool	ft_has_whitespace(char *str);

// cmd_seq.c
t_cmd_seq	*init_cmd_seq(t_lst	*token_list);
t_lst		*init_cmd_seqs(t_lst *token_list);
char		*cmd_seq_get_assignment(t_lst *token_list);
char		**cmd_seq_get_argv(t_lst *token_list);
char		**cmd_seq_get_cmd_args(char *cmd, char **args);

// io.c
t_io	*init_io(char *content, t_flag flag);
t_flag	get_redirection_flag(t_flag *flags);
t_lst	*get_io_list(t_lst *token_list);

// token_search.c
t_lst	*find_token_right(t_lst *current_token_lst, t_flag token_flag, int size);
t_lst	*find_token_left(t_lst	**token_list, t_lst *current_token_lst, t_flag token_flag, int size);

// variable.c
t_env_var	*init_env_variable(char *key, char *value);
t_env_var	*set_env_variable(t_lst *env_var_lst, t_env_var *env_var, char ***envp);
t_env_var	*get_env_variable(char *key, t_lst *env_var_lst);
int			unset_env_variable(char *key, t_lst **env_var_lst);

// variable_helper.c
t_bool		is_str_valid_key(char *key);
char		*get_env_var_value(char *key, t_lst *env_var_lst);
t_env_var	*split_assignment(char *content);

// variable_expansion.c
char	*variable_expansion(const char *arg, t_data *data, t_bool *status);
t_lst	*tokens_variable_expansion(t_lst *tokens_lst, t_data *data);

// execute_new.c
// char	**build_cmd_args(t_ast *node);
// int		execute_command(t_ast *node, t_data *data);
// int		execute_setvalue(t_ast *node, t_data *data);
// int		prepare_args_and_redirect(t_ast *ast, char **args);
// int		execute_pipeline(t_ast *pipe_node, t_data *data);
// int		execute_redirection_out(t_ast *redir_node, t_data *data);
// int		execute_redirection_in(t_ast *redir_node, t_data *data);

// interactive_mode.c
void	ctrlc_handler(int sig);
void	ctrld_handler(t_data *data);

// history.c
void	ft_show_history(void);
void	ft_clear_history(void);

// helper.c
t_bool	ft_isalpha_str(char *str);
t_bool	ft_isalnum_str(char *str);

// debug.c
void	ft_lststrdisplay(t_lst *list);
void	debug_token_list(t_lst *token_list);
void	display_token(t_token *token);
void	display_token_handler(enum token_handler handler);
void	display_token_flag(enum token_flag flag);
void	display_token_flags(enum token_flag *flags);
void	display_env_var(t_data *data);
void	display_cmd_seq(t_lst *cmd_seq_list);

// BUILTINS --
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_cd(char **cmd, t_data *data);
int		builtin_env(char **envp);
int		builtin_exit(char **args, t_data *data);
int		builtin_unset_env(char *key, char ***envp_copy, t_lst **env_var_lst);
int		builtin_export(char **arg, char ***envp, t_data *data);
// int		handle_export(char **args, char ***envp);
int		builtin_history(t_data *data);
int		builtin_temphistory(void);
void	store_history(t_data *data, const char *line);

// export.c
int		ft_addenv(char *arg, char ***envp);
int		ft_setenv(char *key, char *value, char ***envp);
char	*ft_getenv(char *key, char **envp);
int		ft_exportcheck(t_env_var *var, char ***envp);
int		process_args(char **args, char ***envp, t_lst *env_var_lst);

// free.c
void	free_envp(char **envp);
void	free_data(t_data *data);
void	free_str_arr(char **str_arr);
void	free_tokens(t_lst **tokens_lst);
void	free_token(void *content);
void	free_ast_node(void *content);
void	free_env_var(void *content);
void	free_cmd_seqs(t_lst **cmd_seqs);
void	free_cmd_seq(void *content);
void	free_io(void *content);

// exit.c
void	free_exit(int exit_status, t_data *data);

#endif