/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 11:41:22 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/06 20:36:43 by jusilanc         ###   ########.fr       */
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
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	src_size;

	if (src && dst)
	{
		count = 0;
		src_size = ft_strlen(src);
		if (size == 0)
			return (src_size);
		while (count++ < size - 1 && *src)
			*dst++ = *src++;
		*dst = '\0';
		return ((count > src_size) ? --count : src_size);
	}
	return (0);
}
