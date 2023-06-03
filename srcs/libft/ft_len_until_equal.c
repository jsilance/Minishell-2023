/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len_until_equal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:55:56 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/03 21:56:03 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_len_until_equal(const char *str)
{
	size_t	size;

	size = 0;
	while (str && str[size] && str[size] != '=')
		size++;
	return (size);
}
