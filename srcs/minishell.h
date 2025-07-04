/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zernest <zernest@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:51:32 by maxliew           #+#    #+#             */
/*   Updated: 2025/06/19 20:00:34 by zernest          ###   ########.fr       */
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

# define DEBUG 0
# define BUFFER_SIZE 20

// ===== Minishell Types =====

typedef int						t_bool;

// ===== Minishell Variables =====

extern volatile sig_atomic_t	g_sigint_received;

// ===== Minishell Structures =====

enum	e_token_handler
{
	NONE,
	DQUOTE,
	SQUOTE,
};

typedef enum token_flag
{
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
}	t_flag;

typedef struct s_token
{
	char					*content;
	enum e_token_handler	handler;
	t_flag					*flags;
}	t_token;

typedef struct s_cmd_seq
{
	t_lst	*token_list;
	char	*assignment;
	char	**argv;
	t_lst	*io_list;
}	t_cmd_seq;

typedef struct s_io
{
	char	*content;
	t_flag	flag;
	int		fd;
}	t_io;

typedef struct s_env_var
{
	char	*key;
	char	*value;
	t_bool	is_export;
}	t_env_var;

typedef struct s_data
{
	int		should_exit;
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

// --- Setup & Main Processes ---

// minishell.c
void		shell_routine(t_data *data);
t_data		*init_data(int argc, char **argv, char **envp);
char		**get_envp_copy(char **envp, int extra);
t_lst		*init_exported_env_var_lst(char ***envp);

// minishell_extra.c
int			change_exit_code(t_data *data);
void		history_helper(char	*line, t_data *data);

// shell_env.c
int			set_shell_env(t_lst *env_var_lst, char ***envp);
int			set_shlvl(t_lst *env_var_lst, char ***envp);
// int		set_oldpwd_env(t_lst *env_var_lst, char ***envp);
int			set_pwd_env(t_lst *env_var_lst, char ***envp);

// --- Parsing ---

// parse.c
char		*ft_get_line(t_data *data);
char		*ft_get_prompt(t_data *data);
char		*ft_get_prompt_cwd(t_data *data);
char		*ft_get_prompt_environment(void);
t_bool		is_line_quote_ended(char *line, t_bool is_subshell, int *index);

// --- Tokenization ---

// tokenize.c
t_token		*init_token(char *content, \
enum e_token_handler handler, t_flag *flags);
t_lst		*tokenize_line(char *line, t_data *data);
t_lst		*tokenize_str(char *line);
t_token		*handle_dquote(char *line, int *index);
t_token		*handle_squote(char *line, int *index);
t_token		*handle_none(char *line, int *index);
t_lst		*split_token_none(t_lst **token_list);
t_lst		*join_token_list(t_lst **token_list);
t_bool		is_token_cmd(char *content, char *envp[]);
t_bool		is_token_builtin(char *content);
t_bool		is_token_file(char *content);
t_bool		is_token_assignment(char *content);
t_lst		*assign_flags_cmd_arg(t_lst	**token_list);
void		assign_flags_redir_arg(t_lst *token_list);
t_lst		*expand_variable_token_list(t_lst *token_list, t_data *data);

// token_flags.c
t_flag		*init_empty_token_flags(void);
t_bool		has_token_flag(t_flag *flags, t_flag flag);
t_flag		*init_token_flags(t_token *token);
int			token_add_flag(t_flag *flag_arr, t_flag flag);
int			token_add_flags(t_flag *flag_arr, t_flag *new_flag_arr);
int			token_rm_flag(t_flag *flag_arr, t_flag flag);
int			token_rm_flags(t_flag *flag_arr);
t_flag		*token_dup_flag(t_flag *flag_arr);
int			token_add_flags_iter(t_lst *token_list, t_flag flag);
int			apply_token_flags(t_lst	*token_list);
int			tkn_flg_num(t_lst	*token_list, t_flag flag);
t_bool		is_token_flags_empty(t_flag *flags_arr);

// --- Execution ---

// cmd_seq.c
t_cmd_seq	*init_cmd_seq(t_lst	*token_list);
t_lst		*init_cmd_seqs(t_lst *token_list);
char		*cmd_seq_get_assignment(t_lst *token_list);
char		**cmd_seq_get_argv(t_lst *token_list);
char		**cmd_seq_get_cmd_args(char *cmd, char **args);

// io.c
t_io		*init_io(char *content, t_flag flag);
t_flag		get_redirection_flag(t_flag *flags);
t_lst		*get_io_list(t_lst *token_list, int *status);

// execute_function.c
int			execute_command(t_cmd_seq *cmd_seq, t_data *data);
void		exec_handle_parent(pid_t pid, int *status);
void		execve_wrapper(t_cmd_seq *cmd_seq, t_data *data);
void		print_execve_error(char *cmd, int flag, t_data *data);
void		execute_command_norminette(t_cmd_seq *cmd_seq, t_data *data);

// execute.c
char		*find_cmd_path(char *cmd, t_lst *env_var_lst);
char		*search_in_paths(char *cmd, char **paths);
int			is_builtin(char *cmd);
int			run_builtin(char **args, t_data *data);

// execute_new.c
void		cleanup_and_return(t_data *data);
int			execute_cmd_seqs(t_lst *cmd_seqs, t_data *data);
int			execute_assignment(t_cmd_seq *cmd_seq, t_data *data);

// pipe.c
void		parent_process(int *prev_fd, int *pipe_fd, t_bool has_next);
void		child_process(t_lst *cmd_seqs, \
t_data *data, int prev_fd, int *pipe_fd);
int			execute_pipeline(t_lst *cmd_seqs, t_data *data);

// redirections.c
void		apply_redirections(t_lst *io_list, t_data *data);
void		handle_output(char *filename, t_data *data);
void		handle_append(char *filename, t_data *data);
void		handle_input(char *filename, t_data *data);
void		handle_heredoc_redirection(int fd);

// get_next_linestuff
char		*ft_strjoin_free(char *s1, char *s2);
char		*ft_readfile(int fd, char *stash);
char		*get_line(char *stash);
char		*process_stash(char *stash);
char		*get_next_line(int fd);

// heredoc.c
int			handle_heredoc(t_io *io, t_data *data);
int			process_heredocs(t_lst *cmd_seqs, t_data *data);
void		heredoc_sigint_handler(int sig);
void		handle_heredoc_child(t_io *io, t_data *data, int pipe_fd[2]);

// --- Environment Variables ---

// variable.c
t_env_var	*init_env_variable(char *key, char *value);
t_env_var	*set_env_variable(t_lst *env_var_lst, \
t_env_var *env_var, char ***envp);
t_env_var	*get_env_variable(char *key, t_lst *env_var_lst);
int			unset_env_variable(char *key, t_lst **env_var_lst);

// variable_helper.c
t_bool		is_str_valid_key(char *key);
char		*get_env_var_value(char *key, t_lst *env_var_lst);
t_env_var	*split_assignment(char *content);

// variable_expansion.c
char		*variable_expansion(char *arg, t_data *data, t_bool *status);
t_lst		*tokens_variable_expansion(t_lst *tokens_lst, t_data *data);

// split_variable_list.c
t_lst		*split_variable_list(const char *arg);

// interactive_mode.c
void		ctrlc_handler(int sig);
void		ctrld_handler(t_data *data);

// history.c
void		ft_show_history(void);
void		ft_clear_history(void);

// --- Builtins ---
int			builtin_echo(char **args);
int			builtin_pwd(void);
int			builtin_cd(char **cmd, t_data *data);
int			builtin_env(char **envp);
int			builtin_exit(char **args, t_data *data);
int			unset_env(char *key, char ***envp_copy, t_lst **env_var_lst);
int			builtin_unset(char **args, char ***envp_copy, t_lst **env_var_lst);
int			builtin_export(char **arg, char ***envp, t_data *data);
int			builtin_history(t_data *data);
int			builtin_temphistory(void);
void		store_history(t_data *data, const char *line);

// export.c
char		*join_export_identifer(char *key, char *value);
int			ft_exportcheck(t_env_var *var, char ***envp);
int			process_args(char **args, char ***envp, t_lst *env_var_lst);

int			display_export(t_lst *env_var_lst);

// ft_envp.c
int			ft_addenv(char *arg, char ***envp);
int			ft_setenv(char *key, char *value, char ***envp);
char		*ft_getenv(char *key, char **envp);

// free.c
void		free_data(t_data *data);
void		free_str_arr(char **str_arr);
void		free_tokens(t_lst **tokens_lst);
void		free_token(void *content);
void		free_ast_node(void *content);
void		free_env_var(void *content);
void		free_cmd_seqs(t_lst **cmd_seqs);
void		free_cmd_seq(void *content);
void		free_io(void *content);

// exit.c
void		free_exit(int exit_status, t_data *data);

// ft_put_error.c
void		ft_put_error(char *arg, char *error_str);

// helper.c
t_bool		ft_isalpha_str(char *str);
int			count_null_terminated_arr(char **str_arr);
t_bool		ft_has_delimiter(char *str);
t_bool		ft_fully_delimiter(char *str);
t_bool		ft_is_delimiter(char c);

#endif