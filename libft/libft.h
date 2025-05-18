/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxliew <maxliew@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:54:28 by maxliew           #+#    #+#             */
/*   Updated: 2025/05/13 22:24:08 by maxliew          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define FILE_DESCRIPTOR 1
# define LONG_MAX 2147483647
# define NULL_SIZE 1
# define CAPITALIZATION_DIFF 32
# define UINT_MAX 4294967296

// part 1
int		ft_strlen(const char *str);
int		ft_atoi(const char *str);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strrchr(const char *str, int c);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);

// part 2
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strtrim(const char *s1, const char *set);
char	**ft_split(const char *s1, char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
char	*ft_itoa(int n);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

// part 3
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_lst;

t_lst	*ft_lstnew(void *content);
void	ft_lstadd_front(t_lst **lst, t_lst *new);
int		ft_lstsize(t_lst *lst);
t_lst	*ft_lstlast(t_lst *lst);
void	ft_lstadd_back(t_lst **lst, t_lst *new);
void	ft_lstdelone(t_lst *lst, void (*del)(void *));
void	ft_lstclear(t_lst **lst, void (*del)(void *));
void	ft_lstiter(t_lst *lst, void (*f)(void *));
t_lst	*ft_lstmap(t_lst *lst, void *(*f)(void *), void (*del)(void *));

// printf
int		ft_printf(const char *text, ...);
int		process_format_specifier(char f_spec, va_list ap);
void	ft_put_u_nbr_fd(unsigned int n, int fd, int *char_count);
void	ft_put_hex(unsigned long num, const char format, int *char_count);
int		count_digits(int n);

int		fspec_c(va_list ap);
int		fspec_s(va_list ap);
int		fspec_p(va_list ap);
int		fspec_d(va_list ap);
int		fspec_i(va_list ap);
int		fspec_u(va_list ap);
int		fspec_x(va_list ap, const char format);

// extra lst functions
int		ft_lstgetindex(t_lst **lst, t_lst *lst_to_find);
t_lst	*ft_lstgetprevious(t_lst **lst, t_lst *current_lst);
t_lst	*ft_lstindex(t_lst **lst, int to_index);
t_lst	*ft_lstremove(t_lst *lst_del, t_lst *prev_lst, void (*del)(void *));

#endif