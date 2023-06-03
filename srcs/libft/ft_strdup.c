/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:26:21 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/03 16:53:29 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;

	ptr = malloc(sizeof(char) * (ft_strlen((char *)str) + 1));
	if (!ptr)
		return (NULL);
	if (str)
		ft_memcpy(ptr, (char *)str, ft_strlen((char *)str));
	ptr[ft_strlen((char *)str)] = 0;
	return (ptr);
}

char	*ft_strndup(const char *str, int len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (len < 0)
		len = ft_strlen((char *)str);
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	while (str && str[i] && len--)
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
