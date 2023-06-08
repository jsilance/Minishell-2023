/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:41:22 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/08 21:40:11 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1 && *s1)
		ptr[i++] = *s1++;
	while (s2 && *s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

char	*ft_strnstock(char const *s1, char const *s2, int n, int param)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	ptr = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
				+ ft_strlen((char *)s2) + 1));
	if (!ptr)
		return (NULL);
	while (s1 && s1[j])
		ptr[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] && (j < n || n == -1))
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	if (param == 1 || param == 3)
		free((void *)s1);
	if (param == 2 || param == 3)
		free((void *)s2);
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)src;
	if (!dst || !src)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (*src && i < dstsize - 1)
	{
		*dst++ = *src++;
		i++;
	}
	*dst = '\0';
	if (i > ft_strlen(ptr))
		return (i - 1);
	return (ft_strlen(ptr));
}
