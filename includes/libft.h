/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:22:58 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/21 16:05:50 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(const char *s1, const char *charset);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

char	*ft_strdup(const char *str);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

char	**ft_split(char const *s, char c);
char	*ft_strnstock(char const *s1, char const *s2, int n, int param);
char	*ft_strndup(const char *str, int len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	**ft_tabdup(char **tab);
char	*ft_tab_finder(char **env, char *variable);
char	**ft_tab_append(char **old_env, char *new_str);
char	**ft_tab_delone(char **old_env, char *del_str);

char	*ft_strnchr(const char *s, int c, int len);
size_t	ft_len_until_equal(const char *str);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *str, size_t n);

size_t	ft_strlcpy(char *dst, const char *src, size_t size);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strscmp(char *s1, char *s2);
char	*ft_itoa(int nb);

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
char	**ft_tabfree(char **new_tab);

int		ft_is_good_char(char *str, int len);

#endif