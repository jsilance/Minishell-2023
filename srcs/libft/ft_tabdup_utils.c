/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avancoll <avancoll@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 11:34:37 by avancoll          #+#    #+#             */
/*   Updated: 2023/06/21 11:34:58 by avancoll         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tabfree(char **new_tab)
{
	size_t	size;

	size = 0;
	if (!new_tab)
		return (NULL);
	while (new_tab[size])
	{
		free(new_tab[size]);
		size++;
	}
	free(new_tab);
	return (NULL);
}
