/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:32:25 by ysoroko           #+#    #+#             */
/*   Updated: 2021/04/05 17:28:41 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef	struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *str, size_t n);
void				*ft_calloc(size_t count, size_t size);
char				*ft_char_alloc(int n_chars, char c);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_has_other_chars(char *str, const char *allowed_charset);
char				*ft_itoa(int n);
int					ft_longest_strlen_in_strtab(char **str_tab);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
									void (*del)(void *));
t_list				*ft_lstnew(void *content);
int					ft_lstsize(t_list *lst);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_memcmp(const void *str1, const void *str2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *str, int c, size_t len);
int					ft_n_chars_in_str(char *str, char c);
int					ft_n_chars_in_str_tab(char **str_tab, char c);
int					ft_n_ints_in_line(char *str);
void				ft_putchar_fd(char c, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putstr_tab(char **str_tab, int fd);
char				**ft_split(const char *str, char charset);
char				*ft_strchr(const char *str, int c);
char				*ft_strchrset(char *str, char *charset);
char				*ft_strdup(const char *src);
char				*ft_strjoin(char const *pref, char const *suff);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
int					ft_strlcmp(char *s1, char *s2);
size_t				ft_strlcpy(char *dest, const char *src, size_t dstsize);
int					ft_strlen(const char *str);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack,
									const char *needle, size_t len);
char				*ft_strrchr(const char *s, int c);
int					ft_str_tab_len(char **str_tab);
char				*ft_strtrim(char const *str, char const *except);
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_wrong_extension(char *file_name,
											char *expected_extension);
char				*ft_cut_string_at_char(char *str, char c);
char				*ft_free_and_realloc(char *str, int size);
int					ft_strcmp(char *s1, char *s2);
int					ft_strcmptab(char *str_to_compare, char **str_tab);
char				*ft_strstr(char *haystack, char *needle);
t_list				*ft_lstnew_exit(void *content);
void				*ft_calloc_exit(size_t count, size_t size);
char				*ft_strtrim_exit(char *str, char *except);
void				ft_free_str(char **str);
char				*ft_strdup_exit(const char *src);
char				*ft_extract_first_word(char *from, char *separators);
char				*ft_extract_second_word(char *from, char *separators);
int					ft_strchrn(char *str, int c);
char				*ft_cut_string_at_charset(char *str, char *charset);
int					ft_str_only_has_chars_from_charset(char *str,
												char *charset);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcpy_until_c(char *dest, const char *src, char c);
char				*ft_strdup_until_c(const char *src, char c);

#endif
