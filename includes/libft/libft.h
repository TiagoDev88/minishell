/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfilipe- <tfilipe-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 11:42:31 by tfilipe-          #+#    #+#             */
/*   Updated: 2025/04/11 16:41:40 by tfilipe-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_FD
#  define MAX_FD 1024
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/* ************************************************************************** */
/*                               Lists Manipulation                           */
/* ************************************************************************** */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* ************************************************************************** */
/*                               String Manipulation                          */
/* ************************************************************************** */

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);

/* ************************************************************************** */
/*                               Memory Functions                             */
/* ************************************************************************** */

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);

/* ************************************************************************** */
/*                               Character Check Functions                    */
/* ************************************************************************** */

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

/* ************************************************************************** */
/*                               String Iteration Functions                   */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/* ************************************************************************** */
/*                               File Output Functions                        */
/* ************************************************************************** */

void	ft_putchar_fd(char c, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);

/* ************************************************************************** */
/*                               Miscellaneous Functions                      */
/* ************************************************************************** */

char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

/* ************************************************************************** */
/*                               FT_PRINTF Functions                          */
/* ************************************************************************** */

int		ft_printf(const char *str, ...);
int		ft_printf_putstr(char *str);
int		ft_printf_putchar(char c);
int		ft_putnbr_base(unsigned long nbr, char *base);
int		ft_putnbr(int nbr);
int		ft_putnbr_unsigned(unsigned int nbr);
int		ft_check_format(char str, va_list args);
int		ft_putptr(void *ptr);

/* ************************************************************************** */
/*                               Get Next Line Functions                      */
/* ************************************************************************** */

int		gnl_strlen(char *s);
int		has_newline(char *stash);
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
char	*extract_line(char *stash);
char	*update_stash(char *stash);
char	*read_into_stash(int fd, char *stash, char *buffer);

#endif
