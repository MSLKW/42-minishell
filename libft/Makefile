NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

DEPS = libft.h

SRCS_DIR = ./
SRCS_FILES = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c\
ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c\
ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_strjoin.c ft_strtrim.c\
ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_itoa.c ft_strmapi.c ft_striteri.c \
ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_spec.c ft_printf.c ft_printf_utils.c ft_lstgetindex.c ft_lstgetprevious.c \
ft_lstindex.c ft_lstremove.c\

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))

OBJS = $(SRCS:.c=.o)

BONUS_FILES = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
ft_lstclear.c ft_lstiter.c ft_lstmap.c
BONUS = $(addprefix $(SRCS_DIR), $(BONUS_FILES))
BONUS_OBJS = $(BONUS:.c=.o)

.PHONY = all clean fclean re

$(NAME): $(OBJS) $(DEPS)
	ar -rc $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: $(NAME) clean

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

re: fclean all

bonus: $(BONUS_OBJS) $(DEPS)
	ar -rc $(NAME) $(BONUS_OBJS)