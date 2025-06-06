/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:17:46 by ldulling          #+#    #+#             */
/*   Updated: 2025/06/06 17:49:42 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stddef.h>

# define WHITESPACE	" \f\n\r\t\v"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_list_d
{
	void			*content;
	struct s_list_d	*prev;
	struct s_list_d	*next;
}	t_list_d;

\
/* Chars */

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_issign(int c);
int				ft_isprint(int c);
int				ft_isspace(int c);
int				ft_tolower(int c) \
					__attribute__((warn_unused_result));
int				ft_toupper(int c) \
					__attribute__((warn_unused_result));

\
/* Lists doubly-linked */

void			ft_lstadd_back_d(t_list_d **lst, t_list_d *node);
void			ft_lstadd_front_d(t_list_d **lst, t_list_d *node);
void			ft_lstclear_d(t_list_d **lst, void (*del)(void *));
void			ft_lstdelone_d(t_list_d *lst, void (*del)(void *));
void			ft_lstdrop_node_d(t_list_d **lst, t_list_d **node, \
									void (*del)(void *));
void			ft_lstiter_d(t_list_d *lst, void (*f)(void *));
t_list_d		*ft_lstlast_d(t_list_d *lst);
bool			ft_lstnew_back_d(t_list_d **lst, void *content);
t_list_d		*ft_lstnew_d(void *content);
int				ft_lstsize_d(const t_list_d *lst);

\
/* Lists singly-linked */

void			ft_lstadd_back(t_list **lst, t_list *node);
void			ft_lstadd_back_tail(t_list **lst, t_list **tail, t_list *node);
void			ft_lstadd_front(t_list **lst, t_list *node);
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstdrop_node(t_list **lst, t_list **node, \
								void (*del)(void *));
t_list			*ft_lstdup(const t_list *lst, void *(*dup)(const void *), \
							void (*del)(void *));
void			ft_lstinsert_after(t_list **lst, t_list *node);
void			ft_lstinsert_before(t_list **lst, const t_list *cur, \
									t_list *node);
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(const t_list *lst, void *(*f)(const void *), \
							void (*del)(void *));
t_list			*ft_lstnew(void *content);
bool			ft_lstnew_back(t_list **lst, void *content);
bool			ft_lstnew_back_tail(t_list **lst, t_list **tail, void *content);
bool			ft_lstnew_front(t_list **lst, void *content);
t_list			*ft_lstpop_front(t_list **lst);
void			*ft_lstpop_front_content(t_list **lst);
int				ft_lstsize(const t_list *lst);
int				ft_lstsize_non_null(const t_list *lst);
void			ft_lstsort_bubble(t_list **lst, \
								const void *(*cmp)(const void *, const void *));
void			ft_lstsort_merge(t_list **lst, \
								const void *(*cmp)(const void *, const void *));
void			ft_lstswap_head(t_list **lst);

\
/* Memory */

void			ft_bzero(void *s, size_t n) \
					__attribute__((nonnull));
void			*ft_calloc(size_t nmemb, size_t size) \
					__attribute__((malloc, alloc_size(1, 2), \
									warn_unused_result));
void			ft_free_and_null(void **ptr);
void			*ft_memchr(const void *s, int c, size_t n) \
					__attribute__((pure, nonnull));
int				ft_memcmp(const void *s1, const void *s2, size_t n) \
					__attribute__((pure, nonnull));
void			*ft_memcpy(void *dest, const void *src, size_t n) \
					__attribute__((nonnull));
void			*ft_memmove(void *dest, const void *src, size_t n) \
					__attribute__((nonnull));
void			*ft_memset(void *s, int c, size_t n) \
					__attribute__((nonnull));

\
/* Numbers */

int				ft_abs(int j) \
					__attribute__((const, warn_unused_result));
unsigned int	ft_abs_u(int j) \
					__attribute__((const, warn_unused_result));
double			ft_atof(const char *nptr) \
					__attribute__((pure, nonnull, warn_unused_result));
int				ft_atoi(const char *nptr) \
					__attribute__((pure, nonnull, warn_unused_result));
long			ft_atol(const char *nptr) \
					__attribute__((pure, nonnull, warn_unused_result));
bool			ft_inrange_mul_u(size_t a, size_t b, size_t max);
bool			ft_iseven(int value);
bool			ft_isodd(int value);
bool			ft_isoverflow_int(const char *nptr);
bool			ft_isoverflow_long(const char *nptr);
char			*ft_itoa(int n);
long			ft_labs(long j) \
					__attribute__((const, warn_unused_result));
unsigned long	ft_labs_u(long j) \
					__attribute__((const, warn_unused_result));
long			ft_max(long a, long b);
size_t			ft_max_u(size_t a, size_t b);
long			ft_min(long a, long b);
size_t			ft_min_u(size_t a, size_t b);
unsigned int	ft_nbrlen_base(long nbr, unsigned int base);
unsigned int	ft_nbrlen_base_u(size_t nbr, unsigned int base);
int				ft_round_down_even(int value);
size_t			ft_saturating_sub_u(size_t lhs, size_t rhs);

\
/* Put */
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
size_t			ft_putnbr_base_fd(long n, const char *base, int fd);
void			ft_putnbr_fd(int n, int fd);
size_t			ft_putnchar_fd(unsigned char c, size_t n, int fd);
size_t			ft_putnstr_fd(const char *s, size_t n, int fd);
void			ft_putstr_fd(const char *s, int fd);

\
/* Strings */

bool			ft_alphabetic(const char *str1, const char *str2);
char			**ft_split(const char *s, char c);
char			**ft_split_at_index(const char *str, size_t index);
char			*ft_strchr(const char *s, int c) \
					__attribute__((pure, nonnull));
int				ft_strcmp(const char *s1, const char *s2) \
					__attribute__((pure, nonnull));
size_t			ft_strcount_str(const char *big, const char *little);
char			*ft_strdel_sequence(const char *str, const char *sequence);
char			*ft_strdup(const char *s) \
					__attribute__((malloc, nonnull));
bool			ft_strisdigits(const char *s);
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strjoin(const char *s1, const char *s2);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strlcpy_nbr_base(char *dst, long nbr, const char *base, \
									size_t size);
size_t			ft_strlen(const char *s) \
					__attribute__((pure, nonnull));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int				ft_strmatches_any(const char *str, int n, ...);
int				ft_strncmp(const char *s1, const char *s2, size_t n) \
					__attribute__((pure, nonnull));
char			*ft_strndup(const char *s, size_t n) \
					__attribute__((malloc, nonnull));
char			*ft_strnstr(const char *big, const char *little, size_t len);
char			*ft_strrchr(const char *s, int c) \
					__attribute__((pure, nonnull));
char			*ft_strrnstr(const char *big, const char *little, size_t len);
bool			ft_strrplc_part(char **str, const char *rplcmt, size_t start, \
								size_t len);
char			*ft_strrplc_sequence(const char *str, const char *sequence, \
										const char *rplcmt);
char			*ft_strtok(char *str, const char *delim) \
					__attribute__((nonnull (2)));
char			*ft_strtrim(const char *s1, const char *set);
char			*ft_substr(const char *s, unsigned int start, size_t len);

#endif
