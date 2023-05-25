/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 20:28:44 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/25 20:29:19 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dest;
	unsigned char	*str;
	size_t			i;

	i = -1;
	dest = (unsigned char *)dst;
	str = (unsigned char *)src;
	if (!n || dest == src)
		return (dest);
	while (dest && str && ++i < n)
		dest[i] = str[i];
	return (dest);
}
