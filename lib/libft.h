/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylegzoul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:07:57 by ylegzoul          #+#    #+#             */
/*   Updated: 2019/11/21 11:13:18 by ylegzoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

size_t			ft_strlcat(char *dest, char const *src, size_t size);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strcpy(char *dst, const char *src);
size_t			ft_strlcpy(char *dest, char const *src, size_t size);
char			*ft_strnstr(const char *str, const char *to_find, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char charset);

void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, void const *src, size_t n);
void			*ft_memccpy(void *dest, void const *src, int c, size_t size);
void			*ft_memmove(void *s1, void const *s2, size_t n);
void			*ft_memchr(void const *s, int c, size_t n);
int				ft_memcmp(void const *s1, void const *s2, size_t n);
void			*ft_calloc(size_t count, size_t size);

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int nb, int fd);

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);

int				ft_atoi(char const *str);
char			*ft_itoa(int n);
char            *ft_itoa_base(int n, int baselen, char *base);

t_list			*ft_lstnew(void *content);
t_list			*ft_lstnew_malloc(void const *content, int content_size);
int				ft_lstsize(t_list *lst);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **alst, void (*del)(void*));
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstadd_front(t_list **alst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));
void        	ft_print_lst_char(t_list *li);
int	        	ft_tab_to_lst(t_list **li, char *tab, size_t size);

int				ft_putchar_lst(char c, t_list **li);
int				ft_putstr_lst(char *s, t_list **li);
int				ft_putnbr_lst(int nb, t_list **li);
t_list          *ft_putnbr_base_lst(int n, int baselen, char *base, t_list **li);
int	            ft_putnbr_lst_u(unsigned int nb, t_list **li);
t_list          *ft_pnblu(unsigned int n, unsigned int baselen,
char *base, t_list **li);
t_list          *ft_pnblul(unsigned long n, unsigned long baselen,
char *base, t_list **li);

#endif
