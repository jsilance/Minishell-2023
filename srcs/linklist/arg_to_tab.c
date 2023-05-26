/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 12:53:53 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/26 13:08:55 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_to_tab(t_lst_arg *arg)
{
	size_t	len;
	size_t	i;
	char	**tab;

	i = 0;
	len = ft_lst_size(arg);
	tab = (char **)malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	while (len > i && arg)
	{
		tab[i] = ft_strndup(arg->content, arg->len);
		if (!tab[i])
			return (ft_multi_free(tab, i));
		arg = arg->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
