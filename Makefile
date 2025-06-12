NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror
LIBRARIES := -lreadline

SRCS_DIR := ./srcs/
SRCS_FILES :=	minishell.c \
				parse.c \
				history.c \
				tokenize.c \
				execute.c \
				helper.c \
				ast_init.c \
				interactive_mode.c \
				debug.c \
				ast_search.c \
				execute_new.c \
				cd.c \
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c \
				variable.c \
				variable_helper.c \
				variable_expansion.c \
				token_flags.c \
				shell_env.c \
				cmd_seq.c \
				io.c \
				free.c

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
