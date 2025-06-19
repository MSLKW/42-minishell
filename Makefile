NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -g
LIBRARIES := -lreadline

SRCS_DIR := ./srcs/
SRCS_FILES :=	minishell.c \
				get_next_line_utils.c \
				get_next_line.c \
				minishell_extra.c \
				parse.c \
				prompt.c \
				history.c \
				tokenize.c \
				tokenize_expansion.c \
				tokenize_flags.c \
				tokenize_handle.c \
				tokenize_handle_none.c \
				tokenize_join.c \
				execute.c \
				helper.c \
				interactive_mode.c \
				pipe.c \
				redirections.c \
				heredoc.c \
				execute_function.c \
				execute_new.c \
				cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				export_display.c \
				ft_envp.c \
				pwd.c \
				unset.c \
				variable.c \
				variable_helper.c \
				variable_expansion.c \
				split_variable_list.c \
				token_flags.c \
				token_flags_mod.c \
				token_flags_helper.c \
				shell_env.c \
				cmd_seq.c \
				init_cmd_seqs.c \
				io.c \
				free.c \
				free2.c \
				ft_put_error.c \

DEPS_FILES :=	minishell.h

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
DEPS = $(addprefix $(SRCS_DIR), $(DEPS_FILES))
OBJS = $(SRCS:.c=.o)

LIBFT = libft/libft.a

$(NAME): $(OBJS) $(DEPS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LIBRARIES)

$(LIBFT):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY = all clean fclean re

all: $(NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean

re: fclean all
