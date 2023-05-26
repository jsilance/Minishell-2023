/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:22:58 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 11:57:51 by jusilanc         ###   ########.fr       */
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

#endif